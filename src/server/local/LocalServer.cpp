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
	if (_verifyPinCode(card_info.getNumber(), pin))
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

uint64_t LocalServer::getBalance()
{
	if (!_session_card)
	{
		throw runtime_error("No session");
	}
	return _session_card->getBalance();
}

bool LocalServer::changePinCode(const string& new_pin)
{
	if (!_session_card)
	{
		throw runtime_error("No session");
	}
	return ServiceFactory::getCardService()->changePinCode(_session_card->getNumber(), new_pin);
}

bool LocalServer::_verifyPinCode(const string& card_num, const string& pin)
{
	return ServiceFactory::getCardService()->getPinCodeByCard(card_num) == pin;
}

bool LocalServer::canWithdraw(::uint64_t amount)
{
	return _session_card->canWithdraw(amount);
}

uint64_t LocalServer::getWithdrawalFee(::uint64_t amount)
{
	return _session_card->getWithdrawalFee(amount);
}

bool LocalServer::withdraw(::uint64_t amount)
{
	return _session_card->withdraw(amount);
}


