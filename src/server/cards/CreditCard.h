#pragma once

#include "ACard.h"

class CreditCard : public ACard
{
public:
	CreditCard(const string& number) : ACard(number)
	{
	}

	uint64_t getBalance() override;

	uint64_t getWithdrawalFee(const ::uint64_t amount) override;

	uint64_t getOwnBalance();

	uint64_t getCreditBalance();

	virtual  ~CreditCard() = default;

private:
	const static ::uint64_t _minimal_fee;
	const static ::uint64_t _own_fee;
	const static ::uint64_t _credit_fee;

	bool _withdraw(const ::uint64_t amount) override;
};
