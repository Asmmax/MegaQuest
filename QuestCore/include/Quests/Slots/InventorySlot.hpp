#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class InventoryInput;
	class Inventory;

	/// @serializable @shared slots
	class InventorySlot : public QuestInitable
	{
		using InventoryPtr = std::shared_ptr<Inventory>;
	public:
		InventorySlot(const QuestHeaderPtr& quest);
		virtual void Init() override;
		void SetInput(InventoryInput* input);
		InventoryPtr GetInventory() const;

	private:
		InventoryInput* _input;
	};
}
