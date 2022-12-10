#pragma once

#include <memory>

#include "IAccountService.h"
#include "ICardService.h"

using namespace std;

enum class ServiceType
{
	InMemory
};

class ServiceFactory
{
public:
	static void setType(ServiceType type);
	static shared_ptr<ICardService> getCardService();
	static shared_ptr<IAccountService> getAccountService();
private:
	static ServiceType _type;
};
