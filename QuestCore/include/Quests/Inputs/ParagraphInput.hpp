#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class ParagraphSlot;
	class IParagraph;

	/// @serializable @shared inputs
	class ParagraphInput : public Input<IParagraph>
	{
		using Base = Input<IParagraph>;
		using ParagraphSlotPtr = std::shared_ptr<ParagraphSlot>;
		using ParagraphPtr = std::shared_ptr<IParagraph>;

	public:
		ParagraphInput(const ParagraphPtr& paragraph, 
			const ParagraphSlotPtr& slot,
			const QuestHeaderPtr& quest);
	};
}
