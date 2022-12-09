#include "LocalServer.h"

#include "CardNetwork.h"
#include "cards/CardFactory.h"

using namespace std;

ValidStatus LocalServer::validate(const ReadedCardInfo& card_info)
{
	string card_num = card_info.getNumber();
	CardNetwork net(card_num);
	if (!net.compatible())
	{
		return ValidStatus::NotCompatibleNetwork;
	}
	auto validator = net.getValidator();
	if (!validator->validate(card_num))
	{
		return ValidStatus::InvalidCardInfo;
	}
	return ValidStatus::Valid;
}

bool LocalServer::authenticate(const ReadedCardInfo& card_info, const string& pin)
{
	if (validate(card_info) != ValidStatus::Valid)
	{
		return false;
	}
	if (pin == "1234")
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


