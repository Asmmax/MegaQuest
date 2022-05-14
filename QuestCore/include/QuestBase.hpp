#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>

namespace QuestCore
{
	class IParagraph;
	class Inventory;
	class ICaseContainer;
	class ITextView;
	class IButtonPanel;

	struct Root
	{
	private:
		using ParagraphPtr = std::shared_ptr<IParagraph>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
		using TextViewPtr = std::shared_ptr<ITextView>;
		using ButtonsPtr = std::shared_ptr<IButtonPanel>;

	public:
		ParagraphPtr paragraph;
		CaseContainerPtr caseContainer;
		TextViewPtr textView;
		ButtonsPtr buttons;

		void Update();
	};

	class QuestBase
	{
	public:
		using Ptr = std::shared_ptr<QuestBase>;

		QuestBase(const std::vector<Root>& roots);
		virtual ~QuestBase() = default;

		virtual void Update();

	private:
		std::vector<Root> _roots;
	};
};
