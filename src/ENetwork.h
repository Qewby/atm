#pragma once

#include <string>

enum class Network
{
	Visa,
	Mastercard
};

std::string getNetworkVariantString(Network n);

Network getNetworkByNumber(const std::string& number);
