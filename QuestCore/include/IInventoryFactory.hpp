#pragma once
#include <memory>

namespace QuestCore
{
	class Inventory;

	/// @serializable @abstract @shared
	class IInventoryFactory
	{
	protected:
		using InventoryPtr = std::shared_ptr<Inventory>;
	public:
		virtual ~IInventoryFactory() = default;
		virtual InventoryPtr GetInventory() const = 0;
	};
}
