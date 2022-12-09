#pragma once

#include <memory>

#include "ACard.h"
#include "utils/ReadedCardInfo.h"

class CardFactory
{
public:
	static std::unique_ptr<ACard> getCardFromReadedCardInfo(const ReadedCardInfo& info);
};
