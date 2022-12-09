#include "ReadedCardInfo.h"

void ReadedCardInfo::setNumber(const std::string& number)
{
	_number = number;
}

const std::string& ReadedCardInfo::getNumber() const
{
	return _number;
}

std::string ReadedCardInfo::getNumber()
{
	return _number;
}
