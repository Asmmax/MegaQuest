#pragma once
#include "IAction.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Inventory;
	class Item;

	class GiftReceiving: public IAction
	{
		using ItemPtr = std::shared_ptr<Item>;
		using ItemQuery = std::pair<ItemPtr, int>;
	public:
		GiftReceiving(const TextString& name, const std::shared_ptr<Inventory>& inventory);
		virtual TextString GetName() const override;
		virtual void Do() override;

		void AddThings(const ItemPtr& thing, int count);

	private:
		TextString _name;
		std::vector<ItemQuery> _things;
		std::shared_ptr<Inventory> _inventory;
	};
}
