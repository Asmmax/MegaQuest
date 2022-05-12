#pragma once
#include "IParagraph.hpp"
#include "FormatedString.hpp"
#include <vector>
#include <map>

namespace QuestCore
{
	class Inventory;
	class Item;

	class InventoryParagraph: public IParagraph
	{
		using FormPtr = std::shared_ptr<FormBase>;
		using InventoryPtr = std::shared_ptr<Inventory>;
		using ItemPtr = std::shared_ptr<Item>;

		class ItemOrganizer
		{
		public:
			void AddItemOrder(const ItemPtr& item, int order);
			int GetOrder(const ItemPtr& item) const;

		private:
			std::map<ItemPtr, int> _itemOrders;
		};

	public:
		InventoryParagraph(const FormatedString& prefix,
			const TextString& gap,
			const FormatedString& postfix,
			const InventoryPtr& inventory);

		virtual void Print(ITextView& view) override;
		void SetItemOrder(const ItemPtr& item, int order);

	private:
		int GetSumItemCount() const;
		std::vector<std::pair<ItemPtr, int>> GetOrderedItems() const;

	private:
		FormatedString _prefix;
		TextString _gap;
		FormatedString _postfix;
		InventoryPtr _inventory;
		ItemOrganizer _itemOrganizer;
	};
}
