#pragma once

#include <map>

#include "../IAccountService.h"

class InMemoryAccountService : public IAccountService
{
public:
	optional<::uint64_t> getBalanceByAccount(const string& acc_num) override;
private:
	static map<string, map<string, string>> _account_database;
};
