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
	/// @serializable
	class SimpleButtonList : public ButtonListBase, public QuestCore::IButtonGroup
	{
		using ContainerFactoryPtr = std::shared_ptr<QuestCore::ICaseContainerFactory>;
		using CaseContainerPtr = std::shared_ptr<QuestCore::ICaseContainer>;

	public:
		using Ptr = std::shared_ptr<SimpleButtonList>;

		SimpleButtonList(const QuestCore::TextString& error,
			bool show,
			const ContainerFactoryPtr& containerFactory,
			const std::string& containerName);

		virtual void AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback) override;

	protected:
		virtual void UpdateImpl() override;

	private:
		ContainerFactoryPtr _containerFactory;
	};
}
