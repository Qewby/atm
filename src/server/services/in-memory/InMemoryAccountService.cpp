#include "InMemoryAccountService.h"

map<string, map<string, string>> InMemoryAccountService::_account_database = {
        { "0",          {{ "balance", "483647" }}},
		{ "1111111111", {{ "balance", "123400" }}},
		{ "5105105100", {{ "balance", "100000" }}}
};

optional<::uint64_t> InMemoryAccountService::getBalanceByAccount(const string& acc_num)
{
	if (!_account_database.count(acc_num))
	{
		return nullopt;
	}
	return stoul(_account_database[acc_num]["balance"]);
}

bool InMemoryAccountService::setBalanceToAccount(const string& acc_num, const ::uint64_t amount)
{
	if (!_account_database.count(acc_num))
	{
		return false;
	}
	_account_database[acc_num]["balance"] = to_string(amount);
	return true;
}

bool InMemoryAccountService::transferMoneyFromTo(const string& from_acc_num, const string& to_acc_num,
		const ::uint64_t amount)
{
	auto from_balance = getBalanceByAccount(from_acc_num).value();
	if (amount > from_balance)
	{
		return false;
	}
	auto to_balance = getBalanceByAccount(to_acc_num).value();
	from_balance -= amount;
	to_balance += amount;
	setBalanceToAccount(to_acc_num, to_balance);
	setBalanceToAccount(from_acc_num, from_balance);
	return true;
}
