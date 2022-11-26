#pragma once

#include "INumberDecoderStrategy.h"

class VisaNumberDecoderStrategy : public INumberDecoderStrategy
{
public:
	CardNumberInfo decode(const string& number) const override;
};
