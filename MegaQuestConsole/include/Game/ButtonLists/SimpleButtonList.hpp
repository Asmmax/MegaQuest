#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore
{
	class ICaseContainer;
}

namespace Game
{
	class SimpleButtonList : public ButtonListBase
	{
		using DialogWeakPtr = std::weak_ptr<IDialog>;
		using OutputPtr = std::shared_ptr<IOutput>;
		using CaseContainerPtr = std::shared_ptr<QuestCore::ICaseContainer>;

	public:
		using Ptr = std::shared_ptr<SimpleButtonList>;

		SimpleButtonList(const DialogWeakPtr& parent,
			const OutputPtr& output,
			const QuestCore::TextString& error,
			const CaseContainerPtr& container,
			bool show);

		virtual void Update() override;

	private:
		CaseContainerPtr _container;
		bool _show;
	};
}
