#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphSlot;
	class IParagraph;

	/// @serializable
	class ParagraphInput : public ISlot
	{
		using ParagraphSlotPtr = std::shared_ptr<ParagraphSlot>;
		using ParagraphPtr = std::shared_ptr<IParagraph>;

	public:
		ParagraphInput(const ParagraphPtr& paragraph, const ParagraphSlotPtr& slot);
		virtual void Update() override;
		ParagraphPtr GetParagraph() const;

	private:
		ParagraphSlotPtr _slot;
		ParagraphPtr _paragraph;
	};
}
