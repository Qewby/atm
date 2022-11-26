#pragma once

#include <map>
#include <memory>
#include <optional>

#include "CardNumberInfo.h"
#include "INumberDecoderStrategy.h"
#include "ENetwork.h"

using std::shared_ptr;
using std::map;
using std::optional;

class NumberDecoder
{
public:
	bool validate(const string& number) const;

	optional<CardNumberInfo> decode(const string& number) const;

private:
	const static map<Network, shared_ptr<INumberDecoderStrategy>> _strategies;
};
