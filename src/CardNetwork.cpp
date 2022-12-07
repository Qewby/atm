#include "CardNetwork.h"

#include <set>
#include <stdexcept>

#include "spdlog/spdlog.h"

#include "LuhnValidator.h"

using namespace std;

CardNetwork::CardNetwork(const string& number)
{
	const static std::set<std::string> mastercard_iin = { "50", "51", "52", "53", "54", "55" };

	if ((number.length() == 16 || number.length() == 13) && number[0] == '4')
	{
		spdlog::info("Visa card");
		_network = ENetwork::Visa;
	}
	else if (number.length() == 16 && mastercard_iin.count(number.substr(0, 2)))
	{
		spdlog::info("Mastercard card");
		_network = ENetwork::Mastercard;
	}
	else
	{
		spdlog::info("Invalid card number or network not supported(Other)");
		_network = ENetwork::Other;
	}
}

ENetwork CardNetwork::getEnum() const
{
	return _network;
}

std::shared_ptr<ICardValidator> CardNetwork::getValidator()
{
	switch (_network)
	{
	case ENetwork::Mastercard:
	case ENetwork::Visa:
		return make_shared<LuhnValidator>();
	case ENetwork::Other:
		throw invalid_argument("getValidator: Unknown network");
	};
	return std::shared_ptr<ICardValidator>();
}

bool CardNetwork::compatible()
{
	return _network != ENetwork::Other;
}

CardNetwork::operator string() const
{
	switch (_network)
	{
	case ENetwork::Mastercard:
		return "Mastercard";
	case ENetwork::Visa:
		return "Visa";
	case ENetwork::Other:
		return "Other";
	};
	return "Other";
}

ostream& operator<<(ostream& out, const CardNetwork& net)
{
	return out << static_cast<string>(net);
}
