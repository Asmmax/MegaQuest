#pragma once
#include "Game/IButtonList.hpp"
#include <memory>

namespace Game
{
	class SwitchButtonList : public IButtonList
	{
	public:
		using Ptr = std::shared_ptr<SwitchButtonList>;

		virtual void Do(int answer = 0) override;
		virtual void Update() {}
		virtual void SetButtonDoneCallback(const Callback& callback) override;
		void Switch(const IButtonList::Ptr& buttonList);

	private:
		IButtonList::Ptr _currentButtonList;
		Callback _buttonDone;
	};
}
