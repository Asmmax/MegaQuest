#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainerSlot;
	class ICaseContainer;

	/// @serializable
	class CaseContainerInput : public ISlot
	{
		using CaseContainerSlotPtr = std::shared_ptr<CaseContainerSlot>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;

	public:
		CaseContainerInput(const CaseContainerPtr& container, const CaseContainerSlotPtr& slot);
		virtual void Update() override;
		CaseContainerPtr GetCaseContainer() const;

	private:
		CaseContainerSlotPtr _slot;
		CaseContainerPtr _container;
	};
}
