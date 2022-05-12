#pragma once
#include "ICaseContainer.hpp"
#include <vector>

namespace QuestCore
{
	class CaseContainerGroup : public ICaseContainer
	{
	public:
		void Clear();
		void AddCaseContainer(const ICaseContainer::Ptr& container);

		virtual void Print(IButtonPanel& buttonPanel) override;

	private:
		std::vector<ICaseContainer::Ptr> _containers;
	};
}
