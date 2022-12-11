#pragma once

#include "ACard.h"

class DebitCard : public ACard
{
public:
	DebitCard(const string& number) : ACard(number)
	{
	}

	uint64_t getBalance() override;

public:
	~DebitCard() = default;

};
