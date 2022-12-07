#pragma once

#include "ICardValidator.h"

class LuhnValidator : public ICardValidator
{
	bool _validate(const std::string& number) override;
};
