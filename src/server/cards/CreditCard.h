#pragma once

#include "ACard.h"

class CreditCard : public ACard
{
public:
	CreditCard(const string& number) : ACard(number)
	{
	}

	uint64_t getBalance() override;

public:
	~CreditCard() = default;

};
