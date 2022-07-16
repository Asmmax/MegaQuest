#pragma once
#include "IParagraph.hpp"

namespace QuestCore
{
	class TextString;

	/// @serializable
	class ParagraphStateMachine : public IParagraph
	{
	public:
		/// @inject
		void SetState(const std::weak_ptr<IParagraph>& state);

		virtual void Print(ITextView& view) override;
	
	private:
		IParagraph::WeakPtr _state;
	};
}
