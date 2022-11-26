#pragma once

#include <string>
#include <optional>

#include "nlohmann/json.hpp"

#include "ENetwork.h"

using std::string;
using std::optional;

class CardNumberInfo
{
public:
	CardNumberInfo(Network network, const string& issuer, const string& account) : _network(network), _issuer(issuer),
																				   _account(account)
	{
	}

	CardNumberInfo(Network network, string&& issuer, string&& account) : _network(network), _issuer(move(issuer)),
																		 _account(move(account))
	{
	}

	Network getNetwork() const
	{
		return _network;
	}

	string getIssuer() const
	{
		return _issuer;
	}

	string getAccount() const
	{
		return _account;
	}

private:
	Network _network;
	string _issuer;
	string _account;
};

inline void to_json(nlohmann::json& j, const CardNumberInfo& info)
{
	j = nlohmann::json{
			{ "network", getNetworkVariantString(info.getNetwork()) },
			{ "issuer",  info.getIssuer() },
			{ "account", info.getAccount() }};
}

inline void to_json(nlohmann::json& j, const optional<CardNumberInfo>& info)
{
	if (info)
	{
		to_json(j, info.value());
	}
	else
	{
		j = nullptr;
	}
}
