#include "InMemoryAccountService.h"

map<string, map<string, string>> InMemoryAccountService::_account_database = {
		{ "0", {{ "balance", "102937102731029" }}},
		{ "1111111111", {{ "balance", "123400" }}},
		{ "5105105100", {{ "balance", "100000"}}}
};

optional<::uint64_t> InMemoryAccountService::getBalanceByAccount(const string& acc_num)
{
	if (!_account_database.count(acc_num))
	{
		return nullopt;
	}
	return stoul(_account_database[acc_num]["balance"]);
}
