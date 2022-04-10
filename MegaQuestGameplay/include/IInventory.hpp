#pragma once
#include <string>

namespace QuestCore
{
	class IInventory
	{
	public:
		virtual ~IInventory() = default;

		virtual void PutMoney(int money) = 0;
		virtual void ThrowMoney(int money) = 0;
		virtual void PutThing(const std::string& thing) = 0;
		virtual void ThrowThing(const std::string& thing) = 0;
	};
}
