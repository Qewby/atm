#pragma once

#include <string>
#include <optional>

using namespace std;

class IAccountService
{
public:
	virtual optional<string> getBalanceByAccount(const string& acc_num) = 0;

	virtual ~IAccountService() = default;
};
