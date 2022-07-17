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

		virtual void Draw() override;
		void Switch(const IButtonList* buttonList);
		void AddButtonList(const IButtonList::Ptr& buttonList);

		virtual bool IsUpdateAfterDone() const override { return false; }

	protected:
		virtual void UpdateImpl() override;
		virtual void DoImpl(int answer) override;

	private:
		std::vector<IButtonList::Ptr> _buttonLists;
		IButtonList::Ptr _currentButtonList;
	};
}
