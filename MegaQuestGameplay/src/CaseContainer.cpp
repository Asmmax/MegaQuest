#include "CaseContainer.hpp"
#include "IAction.hpp"

#include <assert.h>

using namespace QuestCore;

std::string CaseContainer::GetCases() const
{
	std::string caseString;
	int id = 1;
	auto& actions = GetActions();
	for (auto& action : actions) {
		caseString += std::to_string(id) + " - " + action->GetName() + "\n";
		id++;
	}
	return caseString;
}

int CaseContainer::GetCaseCount() const
{
	return GetActionCount();
}

void CaseContainer::Answer(int caseID)
{
	auto& actions = GetActions();
	assert(caseID < static_cast<int>(actions.size()));

	actions[caseID]->Do();
}
