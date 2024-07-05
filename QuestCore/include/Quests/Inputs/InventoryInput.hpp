#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class InventorySlot;
	class Inventory;

	class InventoryInput : public Input<Inventory>
	{
		using Base = Input<Inventory>;
	public:
		InventoryInput(Inventory* inventory, 
			InventorySlot* slot,
			Quest* quest);
	};
}
