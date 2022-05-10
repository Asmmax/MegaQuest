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

		virtual const std::vector<Case>& GetCases(const std::string& key = std::string()) const override;
		virtual size_t GetCaseCount() const override;

	private:
		std::vector<ICaseContainer::Ptr> _containers;
		mutable std::vector<Case> _cases;
	};
}