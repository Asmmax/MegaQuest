#pragma once
#include "Game/ButtonLists/ButtonListBase.hpp"

namespace QuestCore
{
	class IInventoryFactory;
	class Inventory;
	class Item;
}

namespace Game
{
	class InventoryButtonList : public ButtonListBase
	{
	public:
		InventoryButtonList(const QuestCore::TextString& error, 
			QuestCore::IInventoryFactory* inventoryFactory,
			const std::vector<int>& counts,
			const QuestCore::TextString& putMessage,
			const QuestCore::TextString& throwMessage);

	protected:
		virtual void UpdateImpl() override;

	private:
		void AddPutButton(QuestCore::Item* item, int count);
		void AddThrowButton(QuestCore::Item* item, int count);
		std::vector<std::pair<QuestCore::Item*, int>> GetOrderedItems();

	private:
		QuestCore::IInventoryFactory* _inventoryFactory;
		std::vector<int> _counts;
		QuestCore::TextString _putMessage;
		QuestCore::TextString _throwMessage;
	};
}
