#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphInput;
	class IParagraph;

	/// @serializable @shared slots
	class ParagraphSlot : public QuestInitable
	{
		using ParagraphPtr = std::shared_ptr<IParagraph>;
	public:
		ParagraphSlot(const QuestHeaderPtr& quest);
		virtual void Init() override;
		void SetInput(ParagraphInput* input);
		ParagraphPtr GetParagraph() const;

	private:
		ParagraphInput* _input;
	};
}
