#pragma once

#include "ACard.h"

class DebitCard : public ACard
{
public:
	DebitCard(const string& number) : ACard(number)
	{
	}

	~DebitCard() = default;

};
