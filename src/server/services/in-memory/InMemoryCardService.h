#pragma once

#include <map>

#include "../ICardService.h"

using namespace std;

class InMemoryCardService : public ICardService
{
public:
	optional<string> getPinCodeByCard(const string& card_num) override;

	bool checkCardOurBank(const string& card_num) override;

private:
	static map<string, map<string, string>> _card_database;
};
