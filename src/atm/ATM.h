#pragma once

#include <memory>

#include "../server/IBankServer.h"
#include "../server/LocalServer.h"

class ATM
{
public:
	ATM() : _server(std::make_unique<LocalServer>())
	{
	}

	void run();

private:
	std::unique_ptr<IBankServer> _server;
};
