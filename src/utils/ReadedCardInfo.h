#pragma once

#include <string>

class ReadedCardInfo
{
public:
	ReadedCardInfo() = default;
	ReadedCardInfo(const std::string& number) : _number(number) {}

	std::string getNumber();
	const std::string& getNumber() const;
	void setNumber(const std::string& number);
private:
	std::string _number;
};
