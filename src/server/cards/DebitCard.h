#pragma once

#include "ACard.h"

class DebitCard : public ACard
{
public:
	DebitCard(const string& number) : ACard(number)
	{
	}

	uint64_t getWithdrawalFee(const ::uint64_t amount) override;

	uint64_t getBalance() override;

	virtual  ~DebitCard() = default;

private:
	bool _withdraw(const ::uint64_t amount) override;

};
