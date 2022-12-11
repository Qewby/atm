#pragma once

#include <memory>
#include "server/local/LocalServer.h"


class ATM
{
public:
	ATM() : _server(std::make_unique<LocalServer>())
	{
	}

	void run();

private:
	std::unique_ptr<IBankServer> _server;

	void changePin();
	void withdraw();
};
