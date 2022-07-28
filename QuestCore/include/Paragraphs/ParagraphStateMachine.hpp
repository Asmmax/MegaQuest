#pragma once
#include "IParagraph.hpp"
#include "Quests/QuestInitable.hpp"

namespace QuestCore
{
	class TextString;

	/// @serializable
	class ParagraphStateMachine : public IParagraph, public QuestInitable
	{
	public:
		ParagraphStateMachine(const QuestHeaderPtr& quest);
		/// @inject
		void InitState(const std::weak_ptr<IParagraph>& state);
		void SetState(const std::weak_ptr<IParagraph>& state);

		virtual void Print(ITextView& view) override;
		virtual void Init() override;
	
	private:
		IParagraph::WeakPtr _initState;
		IParagraph::WeakPtr _state;
	};
}
