#pragma once

#include <string>

using namespace std;

class ICard
{
public:
	virtual ~ICard() = default;

	virtual string getNumber() = 0;
};
