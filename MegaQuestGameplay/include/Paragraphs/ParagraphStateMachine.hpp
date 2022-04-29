#pragma once
#include "IParagraph.hpp"
#include "CaseContainer.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphStateMachine : public IParagraph
	{
	public:
		virtual TextString GetQuest() const override;
		virtual CaseContainer& GetCaseContainer() override;

		inline void SetState(const std::shared_ptr<IParagraph>& newState) { _state = newState; }
	
	private:
		std::shared_ptr<IParagraph> _state;
	};
}
