#pragma once
#include <memory>
#include <vector>

namespace QuestCore
{
	class IAction;

	class ActionContainer
	{
	public:
		using ActionList = std::vector<std::shared_ptr<IAction>>;

		virtual ~ActionContainer() = default;

		int GetActionCount() const;
		void AddAction(const std::shared_ptr<IAction>& action);
		void RemoveAction(const std::shared_ptr<IAction>& action);
		const ActionList& GetActions() const;

	private:
		ActionList _actions;
	};
}
