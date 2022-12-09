#pragma once

#include <string>
#include <memory>

#include "ICardValidator.h"

enum class ENetwork
{
	Visa,
	Mastercard,
	Other
};

class CardNetwork
{
public:
	CardNetwork(ENetwork network) : _network(network)
	{
	}

	CardNetwork(const std::string& number);

	operator std::string() const;

	ENetwork getEnum() const;

	std::shared_ptr<ICardValidator> getValidator();

	bool compatible();

private:
	ENetwork _network;
};

std::ostream& operator<<(std::ostream& out, const CardNetwork& net);
