#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class ParagraphInput;
	class IParagraph;

	/// @serializable
	class ParagraphSlot : public ISlot
	{
		using ParagraphPtr = std::shared_ptr<IParagraph>;
	public:
		virtual void Update() override;
		void SetInput(ParagraphInput* input);
		ParagraphPtr GetParagraph() const;

	private:
		ParagraphInput* _input;
	};
}
