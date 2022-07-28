#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"

namespace QuestCore
{
	class InventorySlot;
	class Inventory;
	class Item;
}

namespace Game
{
	/// @serializable
	class InventoryButtonList : public ButtonListBase
	{
		using InventorySlotPtr = std::shared_ptr<QuestCore::InventorySlot>;
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;
		using ItemPtr = std::shared_ptr<QuestCore::Item>;
	public:
		using Ptr = std::shared_ptr<InventoryButtonList>;

		InventoryButtonList(const QuestCore::TextString& error, 
			const InventorySlotPtr& inventorySlot,
			const std::vector<int>& counts,
			const QuestCore::TextString& putMessage,
			const QuestCore::TextString& throwMessage);

	protected:
		virtual void UpdateImpl() override;

	private:
		void AddPutButton(const ItemPtr& item, int count);
		void AddThrowButton(const ItemPtr& item, int count);
		std::vector<std::pair<ItemPtr, int>> GetOrderedItems();

	private:
		InventorySlotPtr _inventorySlot;
		std::vector<int> _counts;
		QuestCore::TextString _putMessage;
		QuestCore::TextString _throwMessage;
	};
}
