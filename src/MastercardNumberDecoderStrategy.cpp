#include "MastercardNumberDecoderStrategy.h"

#include "spdlog/spdlog.h"

CardNumberInfo MastercardNumberDecoderStrategy::decode(const string& number) const
{
	if (number.length() != 16)
	{
		spdlog::info("Invalid Mastercard number length");
		throw std::invalid_argument("Invalid Mastercard number length");
	}
	int bank_number_length = 1 + number[1] - '0';
	std::string bank_number = number.substr(1, bank_number_length);
	std::string account_number = number.substr(bank_number_length + 1, 14 - bank_number_length);
	return CardNumberInfo(Network::Visa, bank_number, account_number);
}
