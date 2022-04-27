#pragma once
#include "ActionContainer.hpp"
#include <memory>
#include <vector>
#include <map>
#include <string>

namespace QuestCore
{
	class ActionMap: public ActionContainer
	{
	public:
		void AddHotAction(const std::string& key, const std::shared_ptr<IAction>& action);
		std::shared_ptr<IAction> GetAction(const std::string& key);

		ActionMap& operator+=(const ActionMap& other);

	private:
		std::map<std::string, std::shared_ptr<IAction>> _map;
	};
}
