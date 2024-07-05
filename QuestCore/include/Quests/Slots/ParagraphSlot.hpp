#pragma once
#include "Quests/Slot.hpp"
#include "IParagraphFactory.hpp"

namespace QuestCore
{
	class ParagraphSlot : public IParagraphFactory, public Slot<IParagraph>
	{
		using Base = Slot<IParagraph>;
	public:
		ParagraphSlot(Quest* quest);
		IParagraph* GetParagraph() const override;
	};
}
