#pragma once

#include <memory>

#include "IBankServer.h"

class LocalServer : public IBankServer
{
public:
	ValidStatus validate(const ReadedCardInfo& card_info) override;

	bool authenticate(const ReadedCardInfo& card_info, const std::string& pin) override;

	void finishSession() override;

	virtual ~LocalServer() = default;

private:
	std::unique_ptr<ReadedCardInfo> _session_card;
};
