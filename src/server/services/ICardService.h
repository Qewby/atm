#pragma once

#include <string>
#include <optional>

using namespace std;

class ICardService
{
public:
	virtual optional<string> getPinCodeByCard(const string& card_num) = 0;
};
