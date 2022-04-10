#pragma once
#include "IAction.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class IInventory;

	class GiftReceiving: public IAction
	{
	public:
		GiftReceiving(const std::string& name);
		virtual std::string GetName() const override;
		virtual void Do() override;

		inline void SetMoney(int money) { _money = money; }
		inline void SetThings(const std::vector<std::string>& things) { _things = things; }
		inline void SetTargetInventory(const std::shared_ptr<IInventory>& inventory) { _inventory = inventory; }

	private:
		std::string _name;
		int _money;
		std::vector<std::string> _things;
		std::shared_ptr<IInventory> _inventory;
	};
}
