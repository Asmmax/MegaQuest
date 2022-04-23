#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphStateMachine;
	class IParagraph;

	class ParagraphChanging : public IAction
	{
	public:
		ParagraphChanging(const TextString& name, const std::shared_ptr<ParagraphStateMachine>& stateMachine, const std::shared_ptr<IParagraph>& nextParagraph);
		virtual TextString GetName() const override;
		virtual void Do() override;
	private:
		TextString _name;
		std::shared_ptr<ParagraphStateMachine> _stateMachine;
		std::shared_ptr<IParagraph> _nextParagraph;
	};
}
