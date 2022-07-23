#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"

namespace QuestCore
{
	class Inventory;
	class Item;
}

namespace Game
{
	/// @serializable
	class InventoryButtonList : public ButtonListBase
	{
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;
		using ItemPtr = std::shared_ptr<QuestCore::Item>;
	public:
		using Ptr = std::shared_ptr<InventoryButtonList>;

		InventoryButtonList(const QuestCore::TextString& error, 
			const InventoryPtr& inventory,
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
		InventoryPtr _inventory;
		std::vector<int> _counts;
		QuestCore::TextString _putMessage;
		QuestCore::TextString _throwMessage;
	};
}
