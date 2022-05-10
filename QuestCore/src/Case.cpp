#include "Case.hpp"
#include "IAction.hpp"

using namespace QuestCore;

void Case::Do()
{
	for (auto& action : actions) {
		action->Do();
	}
}
