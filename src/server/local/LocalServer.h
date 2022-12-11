#pragma once

#include <memory>

#include "server/IBankServer.h"
#include "server/cards/ACard.h"

class LocalServer : public IBankServer
{
public:
	ValidStatus validate(const ReadedCardInfo& card_info) override;

	bool authenticate(const ReadedCardInfo& card_info, const std::string& pin) override;

	bool changePinCode(const string& new_pin) override;

	uint64_t getBalance() override;

	bool canWithdraw(::uint64_t amount) override;

	uint64_t getWithdrawalFee(::uint64_t amount) override;

	bool withdraw(::uint64_t amount) override;

	void finishSession() override;

	virtual ~LocalServer() = default;

private:
	std::unique_ptr<ICard> _session_card;

	bool _verifyPinCode(const string& card_num, const string& pin);
};
