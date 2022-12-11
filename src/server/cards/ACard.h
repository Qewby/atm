#pragma once

#include "ICard.h"

class ACard : public ICard
{
public:
	ACard(const string& number) : _number(number)
	{
	}

	virtual ~ACard() = default;

	string getNumber() override;

	string getAccountNumber();

	bool withdraw(const ::uint64_t amount) override;

	bool canWithdraw(const ::uint64_t amount) override;

private:
	string _number;

	virtual bool _withdraw(const ::uint64_t amount) = 0;
};
