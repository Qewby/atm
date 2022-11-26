#pragma once

#include "CardNumberInfo.h"

struct INumberDecoderStrategy
{
public:
	virtual CardNumberInfo decode(const string& number) const = 0;
};
