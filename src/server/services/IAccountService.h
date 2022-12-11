#pragma once

#include <string>
#include <optional>

using namespace std;

class IAccountService
{
public:
	virtual optional<::uint64_t> getBalanceByAccount(const string& acc_num) = 0;

	virtual ~IAccountService() = default;
};
