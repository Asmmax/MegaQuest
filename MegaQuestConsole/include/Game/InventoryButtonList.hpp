#pragma once
#include "Game/SimpleButtonList.hpp"

namespace QuestCore
{
	class Inventory;
	class Item;
}

namespace Game
{
	class InventoryButtonList : public SimpleButtonList
	{
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;
		using DialogWeakPtr = std::weak_ptr<IDialog>;
		using ItemPtr = std::shared_ptr<QuestCore::Item>;
	public:
		using Ptr = std::shared_ptr<InventoryButtonList>;

		InventoryButtonList(const DialogWeakPtr& parent, 
			const QuestCore::TextString& error, 
			const InventoryPtr& inventory,
			const std::vector<int>& counts,
			const QuestCore::TextString& putMessage,
			const QuestCore::TextString& throwMessage);

		virtual void Update(IOutput& output) override;

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
