#pragma once
#include <memory>

namespace QuestCore
{
	class QuestBase;
	class ITextViewFactory;
	class IButtonPanelFactory;

	class IQuestFactory
	{
	protected:
		using TextViewFactoryPtr = std::shared_ptr<ITextViewFactory>;
		using ButtonsFactoryPtr = std::shared_ptr<IButtonPanelFactory>;

	public:
		using Ptr = std::shared_ptr<IQuestFactory>;

		virtual ~IQuestFactory() = default;
		virtual std::shared_ptr<QuestBase> GetQuest(const TextViewFactoryPtr& viewFactory, const ButtonsFactoryPtr& buttonsFactory) = 0;
	};
}
