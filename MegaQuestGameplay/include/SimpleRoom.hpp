#pragma once
#include "IRoom.hpp"

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
		using InputList = std::map<std::string, std::shared_ptr<IParagraph>>;
	public:
		SimpleRoom(const InputList& inputs, 
			const std::vector<std::string>& hotKeys, 
			const std::map<std::string, ItemPtr>& items,
			const std::map<std::string, InventoryPtr>& inventories);
		virtual const std::shared_ptr<IParagraph>& GetParagraph(const std::string& key) const override;
		virtual const std::vector<std::string>& GetHotKeys() const override;
		virtual const std::map<std::string, ItemPtr>& GetItems() const override;
		virtual const std::map<std::string, InventoryPtr>& GetInventories() const override;

	private:
		std::vector<std::string> _hotKeys;
		std::map<std::string, ItemPtr> _items;
		std::map<std::string, InventoryPtr> _inventories;
		mutable InputList _paragraphs;
	};
}
