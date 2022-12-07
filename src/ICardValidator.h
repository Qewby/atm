#pragma once

#include <string>
#include <algorithm>

#include "spdlog/spdlog.h"

#include "String.h"

class ICardValidator
{
public:
	bool validate(const std::string& number);

private:
	virtual bool _validate(const std::string&) = 0;
};

inline bool ICardValidator::validate(const std::string& number)
{
	if (!allDigits(number))
	{
		spdlog::info(number + " has not digit");
		return false;
	}
	return _validate(number);
}
