#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphStateMachine;
	class IParagraph;

	class ParagraphSwitching : public IAction
	{
	public:
		void SetStateMachine(ParagraphStateMachine* stateMachine);
		void SetNextParagraph(IParagraph* nextParagraph);

		virtual void Do() override;
	private:
		ParagraphStateMachine* _stateMachine;
		IParagraph* _nextParagraph;
	};
}
