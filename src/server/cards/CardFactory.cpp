#include "CardFactory.h"

#include "server/services/ServiceFactory.h"
#include "DebitCard.h"
#include "CreditCard.h"

std::unique_ptr<ICard> CardFactory::getCardFromReadedCardInfo(const ReadedCardInfo& info)
{
	auto type = ServiceFactory::getCardService()->getTypeByCard(info.getNumber());
	if (type == CardType::Debit)
	{
		return make_unique<DebitCard>(info.getNumber());
	}
	else if (type == CardType::Credit)
	{
		return make_unique<CreditCard>(info.getNumber());
	}
}
