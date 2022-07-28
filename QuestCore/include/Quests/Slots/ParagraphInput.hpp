#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphSlot;
	class IParagraph;

	/// @serializable @shared inputs
	class ParagraphInput : public QuestInitable
	{
		using ParagraphSlotPtr = std::shared_ptr<ParagraphSlot>;
		using ParagraphPtr = std::shared_ptr<IParagraph>;

	public:
		ParagraphInput(const ParagraphPtr& paragraph, 
			const ParagraphSlotPtr& slot,
			const QuestHeaderPtr& quest);
		virtual void Init() override;
		ParagraphPtr GetParagraph() const;

	private:
		ParagraphSlotPtr _slot;
		ParagraphPtr _paragraph;
	};
}
