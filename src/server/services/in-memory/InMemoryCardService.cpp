#include "InMemoryCardService.h"

map<string, map<string, string>> InMemoryCardService::_card_database = {
		{ "4111111111111111", {{ "fname", "Ivan" }, { "sname", "Ivanov" }, { "pin", "1234" }, {"type", "Debit"}}},
		{ "5105105105105100", {{ "fname", "Ivan" }, { "sname", "Ivanov" }, { "pin", "1111" }, {"type", "Credit"}, {"limit", "500000"}, {"used", "0"}}}
};

optional<string> InMemoryCardService::getPinCodeByCard(const string& card_num)
{
	if (_card_database.count(card_num))
	{
		return _card_database[card_num]["pin"];
	}
	else
	{
		return nullopt;
	}
}
