#include "CreditCard.h"

#include "server/services/ServiceFactory.h"

uint64_t CreditCard::getBalance()
{
	auto card_service = ServiceFactory::getCardService();
	string card_num = this->getNumber();
	string acc_num = card_service->getAccountByCard(card_num).value();
	::uint64_t own_money = ServiceFactory::getAccountService()->getBalanceByAccount(acc_num).value();
	::uint64_t credit_money = card_service->getRemainedCreditByCard(card_num).value();
	return own_money + credit_money;
}
