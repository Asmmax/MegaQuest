#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class ParagraphSlot;
	class IParagraph;

	class ParagraphInput : public Input<IParagraph>
	{
		using Base = Input<IParagraph>;

	public:
		ParagraphInput(IParagraph* paragraph, 
			ParagraphSlot* slot,
			Quest* quest);
	};
}
