#pragma once

#include <string>

using namespace std;

class ICard
{
public:
	virtual ~ICard() = default;

	virtual string getNumber() = 0;

	virtual bool canWithdraw(const ::uint64_t amount) = 0;

	virtual bool withdraw(const ::uint64_t amount) = 0;

	virtual ::uint64_t getWithdrawalFee(const ::uint64_t amount) = 0;

	virtual ::uint64_t getBalance() = 0;
};
