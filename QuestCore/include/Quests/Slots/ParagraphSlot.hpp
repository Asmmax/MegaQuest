#pragma once
#include "Quests/Slot.hpp"
#include "IParagraphFactory.hpp"

namespace QuestCore
{
	/// @serializable @shared slots
	class ParagraphSlot : public IParagraphFactory, public Slot<IParagraph>
	{
		using Base = Slot<IParagraph>;
	public:
		ParagraphSlot(const QuestPtr& quest);
		virtual ParagraphPtr GetParagraph() const override;
	};
}
