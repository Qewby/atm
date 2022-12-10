#include "LocalServer.h"

#include "spdlog/logger.h"

#include "server/cards/CardNetwork.h"
#include "server/cards/CardFactory.h"
#include "server/services/ServiceFactory.h"

using namespace std;

ValidStatus LocalServer::validate(const ReadedCardInfo& card_info)
{
	string card_num = card_info.getNumber();
	CardNetwork net(card_num);
	if (!net.compatible())
	{
		spdlog::info("Network not compatible");
		return ValidStatus::NotCompatibleNetwork;
	}
	auto validator = net.getValidator();
	if (!validator->validate(card_num))
	{
		spdlog::info("Invalid card number");
		return ValidStatus::InvalidCardInfo;
	}
	if (!ServiceFactory::getCardService()->checkCardOurBank(card_info.getNumber()))
	{
		spdlog::info("Card not in our bank");
		return ValidStatus::NotCompatibleNetwork;
	}
	return ValidStatus::Valid;
}

bool LocalServer::authenticate(const ReadedCardInfo& card_info, const string& pin)
{
	if (validate(card_info) != ValidStatus::Valid)
	{
		return false;
	}
	if (ServiceFactory::getCardService()->getPinCodeByCard(card_info.getNumber()) == pin)
	{
		_session_card = CardFactory::getCardFromReadedCardInfo(card_info);
		return true;
	}
	return false;
}

void LocalServer::finishSession()
{
	_session_card.release();
}


