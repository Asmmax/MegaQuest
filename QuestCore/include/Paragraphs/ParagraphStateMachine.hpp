#pragma once
#include "IParagraph.hpp"
#include "Quests/QuestInitable.hpp"

namespace QuestCore
{
	class TextString;

	class ParagraphStateMachine : public IParagraph, public QuestInitable
	{
	public:
		ParagraphStateMachine(Quest* quest);
		void InitState(IParagraph* state);
		void SetState(IParagraph* state);

		virtual void Print(ITextView& view) override;
		virtual void Init() override;
	
	private:
		IParagraph* _initState;
		IParagraph* _state;
	};
}
