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

		SwitchButtonList(const std::vector<IButtonList*>& targets = std::vector<IButtonList*>());
		virtual void Draw(IOutput& output) override;
		void Switch(const IButtonList* buttonList);
		void AddButtonList(IButtonList* buttonList);

		virtual bool IsUpdateAfterDone() const override { return false; }

	protected:
		virtual void UpdateImpl() override;
		virtual void DoImpl(int answer) override;

	private:
		std::vector<IButtonList*> _buttonLists;
		IButtonList* _currentButtonList;
	};
}
