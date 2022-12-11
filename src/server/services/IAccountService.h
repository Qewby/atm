#pragma once

#include <string>
#include <optional>

using namespace std;

class IAccountService
{
public:
	virtual optional<::uint64_t> getBalanceByAccount(const string& acc_num) = 0;

	virtual bool setBalanceToAccount(const string& acc_num, const ::uint64_t amount) = 0;

	virtual bool transferMoneyFromTo(const string& from_acc_num, const string& to_acc_num, const ::uint64_t amount) = 0;

	virtual ~IAccountService() = default;
};
