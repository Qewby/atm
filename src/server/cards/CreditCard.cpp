#include "CreditCard.h"

#include "spdlog/spdlog.h"

#include "server/services/ServiceFactory.h"

const ::uint64_t CreditCard::_minimal_fee = 500;
const ::uint64_t CreditCard::_own_fee = 1;
const ::uint64_t CreditCard::_credit_fee = 4;

uint64_t CreditCard::getBalance()
{
	auto card_service = ServiceFactory::getCardService();
	string card_num = this->getNumber();
	string acc_num = card_service->getAccountByCard(card_num).value();
	::uint64_t own_money = ServiceFactory::getAccountService()->getBalanceByAccount(acc_num).value();
	::uint64_t credit_money = card_service->getRemainedCreditByCard(card_num).value();
	return own_money + credit_money;
}

uint64_t CreditCard::getWithdrawalFee(const ::uint64_t amount)
{
	::uint64_t own = 0;
	::uint64_t credit = 0;
	if (amount <= this->getOwnBalance())
	{
		own = amount;
	}
	else
	{
		own = this->getOwnBalance();
		credit = amount - own;
	}
	spdlog::info("own");
	spdlog::info(own);
	spdlog::info("credit");
	spdlog::info(credit);
	uint64_t fee = own / 100 * _own_fee + credit / 100 * _credit_fee;
	return fee > _minimal_fee ? fee : _minimal_fee;
}

uint64_t CreditCard::getOwnBalance()
{
	string acc_num = ServiceFactory::getCardService()->getAccountByCard(this->getNumber()).value();
	return ServiceFactory::getAccountService()->getBalanceByAccount(acc_num).value();
}

uint64_t CreditCard::getCreditBalance()
{
	return ServiceFactory::getCardService()->getRemainedCreditByCard(this->getNumber()).value();
}

bool CreditCard::_withdraw(const ::uint64_t amount)
{
	::uint64_t own = 0;
	::uint64_t credit = 0;
	if (amount <= this->getOwnBalance())
	{
		own = amount;
	}
	else
	{
		own = this->getOwnBalance();
		credit = amount - own;
	}
	if (!ServiceFactory::getAccountService()->transferMoneyFromTo(this->getAccountNumber(), "0", own))
	{
		return false;
	}
	if (!ServiceFactory::getCardService()->increaseCreditUsed(this->getNumber(), credit))
	{
		return false;
	}
	return true;
}
