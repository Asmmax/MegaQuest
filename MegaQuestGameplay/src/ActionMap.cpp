#include "ActionMap.hpp"

using namespace QuestCore;

void ActionMap::AddHotAction(const std::string& key, const std::shared_ptr<IAction>& action)
{
	AddAction(action);
	_map.emplace(key, action);
}

std::shared_ptr<IAction> ActionMap::GetAction(const std::string& key)
{
	auto foundIt = _map.find(key);
	if (foundIt == _map.end()) {
		return std::shared_ptr<IAction>();
	}
	return foundIt->second;
}

ActionMap& ActionMap::operator+=(const ActionMap& other)
{
	ActionContainer::operator+=(other);

	for (auto& action : other._map) {
		_map.emplace(action.first, action.second);
	}
	return *this;
}
