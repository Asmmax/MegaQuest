#pragma once
#include "ActionSwitcher.hpp"

namespace QuestCore
{
	class AutoActionSwitcher : public ActionSwitcher
	{
	public:
		AutoActionSwitcher();
		virtual void Do() override;

		void SetFinalAction(int actionID);

	private:
		bool _isInited;
		int _finalActionId;
	};
}
