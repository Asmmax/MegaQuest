#pragma once
#include "Quests/Slot.hpp"

namespace QuestCore
{
	class IParagraph;

	/// @serializable @shared slots
	class ParagraphSlot : public Slot<IParagraph>
	{
		using Base = Slot<IParagraph>;
		using ParagraphPtr = std::shared_ptr<IParagraph>;
	public:
		ParagraphSlot(const QuestHeaderPtr& quest);
		ParagraphPtr GetParagraph() const;
	};
}
