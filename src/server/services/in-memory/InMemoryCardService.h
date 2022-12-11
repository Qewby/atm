#pragma once

#include <map>

#include "../ICardService.h"

using namespace std;

class InMemoryCardService : public ICardService
{
public:
	optional<string> getPinCodeByCard(const string& card_num) override;

	bool checkCardOurBank(const string& card_num) override;

	optional<CardType> getTypeByCard(const string& card_num) override;

	optional<string> getAccountByCard(const string& card_num) override;

	optional<::uint64_t> getCreditLimitByCard(const string& card_num) override;

	optional<::uint64_t> getRemainedCreditByCard(const string& card_num) override;

	optional<::uint64_t> getUsedCreditLimitByCard(const string& card_num) override;

	bool setCreditUsed(const string& card_num, const ::uint64_t amount) override;

	bool increaseCreditUsed(const string& card_num, const ::uint64_t amount) override;

	bool changePinCode(const string& card_num, const string& pin) override;

private:
	static map<string, map<string, string>> _card_database;
};
