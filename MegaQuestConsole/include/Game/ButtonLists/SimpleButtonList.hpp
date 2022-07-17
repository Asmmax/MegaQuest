#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"
#include "IButtonGroup.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore
{
	class ICaseContainer;
}

namespace Game
{
	class SimpleButtonList : public ButtonListBase, public QuestCore::IButtonGroup
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using CaseContainerPtr = std::shared_ptr<QuestCore::ICaseContainer>;

	public:
		using Ptr = std::shared_ptr<SimpleButtonList>;

		SimpleButtonList(const OutputPtr& output,
			const QuestCore::TextString& error,
			bool show,
			const CaseContainerPtr& container);

		virtual void AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback) override;

	protected:
		virtual void UpdateImpl() override;

	private:
		CaseContainerPtr _container;
	};
}
