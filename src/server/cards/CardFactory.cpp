#include "CardFactory.h"

std::unique_ptr<ACard> CardFactory::getCardFromReadedCardInfo(const ReadedCardInfo& info)
{
	return std::unique_ptr<ACard>();
}
