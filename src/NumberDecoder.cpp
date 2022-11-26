#include "NumberDecoder.h"

#include "spdlog/spdlog.h"

#include "VisaNumberDecoderStrategy.h"
#include "MastercardNumberDecoderStrategy.h"

static auto getStrategies = []()
{
	map<Network, shared_ptr<INumberDecoderStrategy>> result;
	result.insert({ Network::Visa, std::make_shared<VisaNumberDecoderStrategy>() });
	result.insert({ Network::Mastercard, std::make_shared<MastercardNumberDecoderStrategy>() });
	return result;
};

const map<Network, shared_ptr<INumberDecoderStrategy>> NumberDecoder::_strategies = getStrategies();

bool NumberDecoder::validate(const string& number) const
{
	int nDigits = number.length();

	int nSum = 0, isSecond = false;
	for (int i = nDigits - 1; i >= 0; i--)
	{

		int d = number[i] - '0';

		if (isSecond == true)
			d = d * 2;

		// We add two digits to handle
		// cases that make two digits after
		// doubling
		nSum += d / 10;
		nSum += d % 10;

		isSecond = !isSecond;
	}
	return (nSum % 10 == 0);
}

optional<CardNumberInfo> NumberDecoder::decode(const string& number) const
{
	if (!validate(number))
	{
		spdlog::info("number not valid");
		return std::nullopt;
	}
	try
	{
		Network network = getNetworkByNumber(number);
		if (_strategies.count(network))
		{
			return _strategies.at(network)->decode(number);
		}
		else
		{
			spdlog::info("no network decode strategy");
			return std::nullopt;
		}
	}
	catch (...)
	{
		spdlog::info("error during decoding");
		return std::nullopt;
	}
}
