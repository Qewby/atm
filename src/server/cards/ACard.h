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

private:
	string _number;
};
