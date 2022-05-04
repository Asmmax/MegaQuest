#pragma once
#include <memory>

namespace QuestCore
{
	class Item;
	class Inventory;

	class Value 
	{
	public:
		virtual ~Value() = default;
		virtual int Get() const = 0;
	};

	class SimpleValue : public Value
	{
	public:
		SimpleValue(int value = 0);
		virtual int Get() const override;
	private:
		int _value;
	};

	class InventoryValue : public Value
	{
	public:
		InventoryValue(const std::shared_ptr<Item>& item, const std::shared_ptr<Inventory>& inventory);
		virtual int Get() const override;
	private:
		std::shared_ptr<Inventory> _inventory;
		std::shared_ptr<Item> _item;
	};
}