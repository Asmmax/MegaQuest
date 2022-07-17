#pragma once
#include "Game/IButtonList.hpp"
#include <memory>
#include <vector>

namespace Game
{
	/// @serializable
	class SwitchButtonList : public IButtonList
	{
	public:
		using Ptr = std::shared_ptr<SwitchButtonList>;

		SwitchButtonList(const std::vector<IButtonList::Ptr>& targets = std::vector<IButtonList::Ptr>());
		virtual void Draw(IOutput& output) override;
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
