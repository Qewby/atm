#include "DebitCard.h"

#include "server/services/ServiceFactory.h"

uint64_t DebitCard::getBalance()
{
	string acc_num = ServiceFactory::getCardService()->getAccountByCard(this->getNumber()).value();
	return ServiceFactory::getAccountService()->getBalanceByAccount(acc_num).value();
}
