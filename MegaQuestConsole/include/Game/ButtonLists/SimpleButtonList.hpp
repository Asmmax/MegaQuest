#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"
#include "IButtonGroup.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore
{
	class ICaseContainerFactory;
	class ICaseContainer;
}

namespace Game
{
	class SimpleButtonList : public ButtonListBase, public QuestCore::IButtonGroup
	{
	public:
		SimpleButtonList(const QuestCore::TextString& error,
			bool show,
			QuestCore::ICaseContainerFactory* containerFactory);

		virtual void AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback) override;

	protected:
		virtual void UpdateImpl() override;

	private:
		QuestCore::ICaseContainerFactory* _containerFactory;
	};
}
