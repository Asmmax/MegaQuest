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
		/// @inject
		void SetStateMachine(const std::weak_ptr<ParagraphStateMachine>& stateMachine);
		/// @inject
		void SetNextParagraph(const std::weak_ptr<IParagraph>& nextParagraph);

		virtual void Do() override;
	private:
		std::weak_ptr<ParagraphStateMachine> _stateMachine;
		std::weak_ptr<IParagraph> _nextParagraph;
	};
}
