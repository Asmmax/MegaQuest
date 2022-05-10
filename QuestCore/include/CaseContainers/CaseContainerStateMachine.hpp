#pragma once
#include "ICaseContainer.hpp"

namespace QuestCore
{
	class CaseContainerStateMachine : public ICaseContainer
	{
	public:
		virtual const std::vector<Case>& GetCases(const std::string& key = std::string()) const override;
		virtual size_t GetCaseCount() const override;

		inline void SetState(const ICaseContainer::Ptr& newState) { _state = newState; }

	private:
		ICaseContainer::Ptr _state;
	};
}