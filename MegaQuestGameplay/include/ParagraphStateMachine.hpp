#pragma once
#include "IParagraph.hpp"

#include <memory>

namespace QuestCore
{
	class ParagraphStateMachine : public IParagraph
	{
	public:
		virtual TextString GetQuest() const override;
		virtual ActionMap& GetActionContainer() override;

		inline void SetState(const std::shared_ptr<IParagraph>& newState) { _state = newState; }
	
	private:
		std::shared_ptr<IParagraph> _state;
	};
}
