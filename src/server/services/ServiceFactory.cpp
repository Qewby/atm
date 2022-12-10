#include "ServiceFactory.h"

#include "in-memory/InMemoryCardService.h"
#include "in-memory/InMemoryAccountService.h"

ServiceType ServiceFactory::_type = ServiceType::InMemory;

void ServiceFactory::setType(ServiceType type)
{
	_type = type;
}

shared_ptr<ICardService> ServiceFactory::getCardService()
{
	switch (_type)
	{
	case ServiceType::InMemory:
		return make_shared<InMemoryCardService>();
	}
	return shared_ptr<ICardService>();
}

shared_ptr<IAccountService> ServiceFactory::getAccountService()
{
	switch (_type)
	{
	case ServiceType::InMemory:
		return make_shared<InMemoryAccountService>();
	}
	return shared_ptr<IAccountService>();
}
