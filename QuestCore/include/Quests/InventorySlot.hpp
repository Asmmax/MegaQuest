#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class InventoryInput;
	class Inventory;

	/// @serializable
	class InventorySlot : public ISlot
	{
		using InventoryPtr = std::shared_ptr<Inventory>;
	public:
		virtual void Update() override;
		void SetInput(InventoryInput* input);
		InventoryPtr GetInventory() const;

	private:
		InventoryInput* _input;
	};
}
