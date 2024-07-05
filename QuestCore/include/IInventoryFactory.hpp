#pragma once
#include <memory>

namespace QuestCore
{
	class Inventory;

	class IInventoryFactory
	{
	public:
		virtual ~IInventoryFactory() = default;
		virtual Inventory* GetInventory() const = 0;
	};
}
