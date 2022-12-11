#include "DebitCard.h"

#include "server/services/ServiceFactory.h"

uint64_t DebitCard::getBalance()
{
	string acc_num = ServiceFactory::getCardService()->getAccountByCard(this->getNumber()).value();
	return ServiceFactory::getAccountService()->getBalanceByAccount(acc_num).value();
}

uint64_t DebitCard::getWithdrawalFee(const ::uint64_t amount)
{
	return 0;
}

bool DebitCard::_withdraw(const ::uint64_t amount)
{
	return ServiceFactory::getAccountService()->transferMoneyFromTo(this->getAccountNumber(), "0", amount);
}
