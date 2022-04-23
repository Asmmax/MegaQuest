#pragma once
#include "IAction.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Inventory;
	class ItemInfo;

	class GiftReceiving: public IAction
	{
		using ItemInfoPtr = std::shared_ptr<ItemInfo>;
		using Item = std::pair<ItemInfoPtr, int>;
	public:
		GiftReceiving(const TextString& name, const std::shared_ptr<Inventory>& inventory);
		virtual TextString GetName() const override;
		virtual void Do() override;

		void AddThings(const ItemInfoPtr& thing, int count);

	private:
		TextString _name;
		std::vector<Item> _things;
		std::shared_ptr<Inventory> _inventory;
	};
}
