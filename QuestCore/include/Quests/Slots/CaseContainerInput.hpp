#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainerSlot;
	class ICaseContainer;

	/// @serializable @shared inputs
	class CaseContainerInput : public QuestInitable
	{
		using CaseContainerSlotPtr = std::shared_ptr<CaseContainerSlot>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		CaseContainerInput(const CaseContainerPtr& container, 
			const CaseContainerSlotPtr& slot,
			const QuestHeaderPtr& quest);

		virtual void Init() override;
		CaseContainerPtr GetCaseContainer() const;

	private:
		CaseContainerSlotPtr _slot;
		CaseContainerPtr _container;
	};
}
