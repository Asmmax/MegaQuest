#pragma once
#include "ReplayAction.hpp"
#include <vector>

namespace Game
{
	class ReplayAction;

	class ReplayManager
	{
	public:
		void PushAction(const ReplayAction& action);
		void Store();
		void Restore();

	private:
		void Save();
		void Load();

	private:
		std::vector<ReplayAction> _actions;
	};
}