#include "InMemoryCardService.h"

map<string, map<string, string>> InMemoryCardService::_card_database = {
		{ "4111111111111111", {{ "account", "1111111111" }, { "fname", "Ivan" }, { "sname", "Ivanov" }, { "pin", "1234" }, { "type", "Debit" }}},
		{ "5105105105105100", {{ "account", "5105105100" }, { "fname", "Ivan" }, { "sname", "Ivanov" }, { "pin", "1111" }, { "type", "Credit" }, { "limit", "500000" }, { "used", "0" }}}
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

bool InMemoryCardService::checkCardOurBank(const string& card_num)
{
	return _card_database.count(card_num);
}

bool InMemoryCardService::changePinCode(const string& card_num, const string& pin)
{
	if (!_card_database.count(card_num))
	{
		return false;
	}
	_card_database[card_num]["pin"] = pin;
	return true;
}

optional<CardType> InMemoryCardService::getTypeByCard(const string& card_num)
{
	if (!_card_database.count(card_num))
	{
		return nullopt;
	}
	string type = _card_database[card_num]["type"];
	if (type == "Debit")
	{
		return CardType::Debit;
	}
	else if (type == "Credit")
	{
		return CardType::Credit;
	}
	else
	{
		return nullopt;
	}
}

optional<string> InMemoryCardService::getAccountByCard(const string& card_num)
{
	if (!_card_database.count(card_num))
	{
		return nullopt;
	}
	return card_num.substr(6);
}

optional<::uint64_t> InMemoryCardService::getCreditLimitByCard(const string& card_num)
{
	if (!_card_database.count(card_num))
	{
		return nullopt;
	}
	return stoul(_card_database[card_num]["limit"]);
}

optional<::uint64_t> InMemoryCardService::getUsedCreditLimitByCard(const string& card_num)
{
	if (!_card_database.count(card_num))
	{
		return nullopt;
	}
	return stoul(_card_database[card_num]["used"]);
}

optional<::uint64_t> InMemoryCardService::getRemainedCreditByCard(const string& card_num)
{
	if (!_card_database.count(card_num))
	{
		return nullopt;
	}
	return getCreditLimitByCard(card_num).value() - getUsedCreditLimitByCard(card_num).value();
}

bool InMemoryCardService::increaseCreditUsed(const string& card_num, const ::uint64_t amount)
{
	auto used_balance = getUsedCreditLimitByCard(card_num).value();
	auto limit = getCreditLimitByCard(card_num).value();
	used_balance += amount;
	if (used_balance > limit)
	{
		return false;
	}
	else
	{
		return setCreditUsed(card_num, used_balance);
	}
}

bool InMemoryCardService::setCreditUsed(const string& card_num, const ::uint64_t amount)
{
	if (!_card_database.count(card_num))
	{
		return false;
	}
	_card_database[card_num]["used"] = to_string(amount);
	return true;
}
