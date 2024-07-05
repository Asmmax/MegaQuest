#pragma once
#include "ICaseContainer.hpp"
#include <vector>

namespace QuestCore
{
	class CaseContainerGroup : public ICaseContainer
	{
	public:
		CaseContainerGroup(const std::vector<ICaseContainer*>& children);

		void Clear();
		void AddCaseContainer(ICaseContainer* container);

		virtual void Print(IButtonGroup& buttons) override;

	private:
		std::vector<ICaseContainer*> _containers;
	};
}
