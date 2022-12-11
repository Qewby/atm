#include "CardFactory.h"

#include "DebitCard.h"

std::unique_ptr<ACard> CardFactory::getCardFromReadedCardInfo(const ReadedCardInfo& info)
{
	return make_unique<DebitCard>(info.getNumber());
}
