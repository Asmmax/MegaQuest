#pragma once
#include "IInventory.hpp"
#include <vector>

namespace Player
{
	class PlayerInventory : public QuestCore::IInventory
	{
	public:
		virtual void PutMoney(int money) override;
		virtual void ThrowMoney(int money) override;
		virtual void PutThing(const std::string& thing) override;
		virtual void ThrowThing(const std::string& thing)override;

		std::string GetContains();

	private:
		int _money;
		std::vector<std::string> _items;
	};
}
