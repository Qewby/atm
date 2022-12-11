#pragma once

#include "utils/ReadedCardInfo.h"

using namespace std;

enum class ValidStatus
{
	NotCompatibleNetwork,
	InvalidCardInfo,
	Valid
};

class IBankServer
{
public:
	virtual ValidStatus validate(const ReadedCardInfo& card_info) = 0;

	virtual bool authenticate(const ReadedCardInfo& card_info, const std::string& pin) = 0;

	virtual uint64_t getBalance() = 0;

	virtual bool changePinCode(const string& new_pin) = 0;

	virtual bool canWithdraw(::uint64_t amount) = 0;

	virtual ::uint64_t getWithdrawalFee(::uint64_t amount) = 0;

	virtual bool withdraw(::uint64_t amount) = 0;

	virtual void finishSession() = 0;

	virtual ~IBankServer() = default;
};
