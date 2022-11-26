#include "ENetwork.h"

#include <set>
#include <stdexcept>

#include "spdlog/spdlog.h"

std::string getNetworkVariantString(Network n)
{
	switch (n)
	{
	case Network::Mastercard:
		return "Mastercard";
	case Network::Visa:
		return "Visa";
	};
	return "";
}

Network getNetworkByNumber(const std::string& number)
{
	const static std::set<std::string> mastercard_iin = { "50", "51", "52", "53", "54", "55" };
	if ((number.length() == 16 || number.length() == 13) && number[0] == '4')
	{
		spdlog::info("Visa card");
		return Network::Visa;
	}
	else if (number.length() == 16 && mastercard_iin.count(number.substr(0, 2)))
	{
		spdlog::info("Mastercard card");
		return Network::Mastercard;
	}
	else
	{
		spdlog::info("Invalid card number or network not supported");
		throw std::invalid_argument("Invalid card number or network not supported");
	}
}
