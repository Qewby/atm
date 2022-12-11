#pragma once

#include <string>
#include <optional>

using namespace std;

enum class CardType
{
	Debit, Credit
};

class ICardService
{
public:
	virtual optional<string> getPinCodeByCard(const string& card_num) = 0;

	virtual optional<CardType> getTypeByCard(const string& card_num) = 0;

	virtual optional<string> getAccountByCard(const string& card_num) = 0;

	virtual optional<::uint64_t> getCreditLimitByCard(const string& card_num) = 0;

	virtual optional<::uint64_t> getUsedCreditLimitByCard(const string& card_num) = 0;

	virtual optional<::uint64_t> getRemainedCreditByCard(const string& card_num) = 0;

	virtual bool checkCardOurBank(const string& card_num) = 0;

	virtual bool changePinCode(const string& card_num, const string& pin) = 0;

	virtual ~ICardService() = default;
};
