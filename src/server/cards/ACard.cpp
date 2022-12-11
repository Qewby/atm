#include "ACard.h"

string ACard::getNumber()
{
	return _number;
}

bool ACard::canWithdraw(const ::uint64_t amount)
{
	return (amount + getWithdrawalFee(amount)) <= this->getBalance();
}

string ACard::getAccountNumber()
{
	return _number.substr(6);
}

bool ACard::withdraw(const ::uint64_t amount)
{
	if (!canWithdraw(amount))
	{
		return false;
	}
	if (!_withdraw(amount + getWithdrawalFee(amount)))
	{
		return false;
	}
	return true;
}
