#pragma once
#include "IParagraph.hpp"

namespace QuestCore
{
	class TextString;

	class ParagraphStateMachine : public IParagraph
	{
	public:
		virtual TextString GetText() const override;

		inline void SetState(const IParagraph::Ptr& newState) { _state = newState; }
	
	private:
		IParagraph::Ptr _state;
	};
}
