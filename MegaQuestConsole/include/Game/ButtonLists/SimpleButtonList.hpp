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
			const CaseContainerPtr& container,
			bool show);

		virtual void Update() override;
		virtual void AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback) override;

	private:
		CaseContainerPtr _container;
		bool _show;
	};
}
