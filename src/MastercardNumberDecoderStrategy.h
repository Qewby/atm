#pragma once

#include "INumberDecoderStrategy.h"

class MastercardNumberDecoderStrategy : public INumberDecoderStrategy
{
public:
	CardNumberInfo decode(const string& number) const override;
};
