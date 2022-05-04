#pragma once
#include "IParagraph.hpp"
#include "FormatedString.hpp"
#include "CaseContainer.hpp"
#include <vector>

namespace QuestCore
{
	class Inventory;
	class Item;

	class InventoryParagraph: public IParagraph
	{
		using FormPtr = std::shared_ptr<FormBase>;
		using ItemPtr = std::shared_ptr<Item>;
	public:
		InventoryParagraph(const FormatedString& prefix,
			const TextString& gap,
			const FormatedString& postfix,
			const std::shared_ptr<Inventory>& inventory);

		virtual TextString GetQuest() const override;
		virtual CaseContainer& GetCaseContainer() override;
		void SetItemOrder(const ItemPtr& item, int order);

	private:
		std::vector<std::pair<ItemPtr, int>> GetOrderedItems() const;

	private:
		CaseContainer _cases;
		FormatedString _prefix;
		TextString _gap;
		FormatedString _postfix;
		std::shared_ptr<Inventory> _inventory;
		std::map<ItemPtr, int> _itemOrders;
	};
}