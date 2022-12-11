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

	void finishSession() override;

	virtual ~LocalServer() = default;

private:
	std::unique_ptr<ACard> _session_card;

	bool _verifyPinCode(const string& card_num, const string& pin);
};
