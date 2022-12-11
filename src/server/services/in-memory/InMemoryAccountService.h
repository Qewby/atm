#pragma once

#include <map>

#include "../IAccountService.h"

class InMemoryAccountService : public IAccountService
{
public:
	optional<::uint64_t> getBalanceByAccount(const string& acc_num) override;

	bool setBalanceToAccount(const string& acc_num, const ::uint64_t amount) override;

	bool transferMoneyFromTo(const string& from_acc_num, const string& to_acc_num, const ::uint64_t amount) override;

private:
	static map<string, map<string, string>> _account_database;
};
