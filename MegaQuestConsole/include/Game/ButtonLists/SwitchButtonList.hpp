#pragma once
#include "Game/IButtonList.hpp"
#include <memory>
#include <vector>

namespace Game
{
	class SwitchButtonList : public IButtonList
	{
	public:
		using Ptr = std::shared_ptr<SwitchButtonList>;

		virtual void Do(int answer = 0) override;
		virtual void Update() override;
		virtual void Draw() override;
		void Switch(const IButtonList* buttonList);
		void AddButtonList(const IButtonList::Ptr& buttonList);

	private:
		std::vector<IButtonList::Ptr> _buttonLists;
		IButtonList::Ptr _currentButtonList;
	};
}
