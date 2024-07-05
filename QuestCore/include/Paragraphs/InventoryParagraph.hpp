#pragma once
#include "IParagraph.hpp"
#include "FormatedString.hpp"
#include <vector>
#include <map>

namespace QuestCore
{
	class Inventory;
	class Item;

	struct ItemOrder
	{
		Item* item;
		int order;
	};

	class InventoryParagraph: public IParagraph
	{
		class ItemOrganizer
		{
		public:
			void AddItemOrder(Item* item, int order);
			int GetOrder(Item* item) const;

		private:
			std::map<Item*, int> _itemOrders;
		};

	public:
		InventoryParagraph(const FormatedString& prefix,
			const TextString& gap,
			const FormatedString& postfix,
			Inventory* inventory,
			const std::vector<ItemOrder>& itemOrders = std::vector<ItemOrder>());

		virtual void Print(ITextView& view) override;
		void SetItemOrder(Item* item, int order);

	private:
		int GetSumItemCount() const;
		std::vector<std::pair<Item*, int>> GetOrderedItems() const;

	private:
		FormatedString _prefix;
		TextString _gap;
		FormatedString _postfix;
		Inventory* _inventory;
		ItemOrganizer _itemOrganizer;
	};
}
