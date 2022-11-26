#include "VisaNumberDecoderStrategy.h"

#include "spdlog/spdlog.h"

CardNumberInfo VisaNumberDecoderStrategy::decode(const string& number) const
{
	if (number.length() != 13 && number.length() != 16)
	{
		spdlog::info("Invalid Visa number length");
		throw std::invalid_argument("Invalid Visa number length");
	}
	std::string bank_number = number.substr(1, 5);
	std::string account_number;
	if (number.length() == 13)
	{
		account_number = number.substr(6, 6);
	}
	else
	{
		account_number = number.substr(6, 9);
	}
	return CardNumberInfo(Network::Visa, bank_number, account_number);
}
