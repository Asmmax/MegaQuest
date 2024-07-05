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
		InventoryValue(Item* item, Inventory* inventory);
		virtual int Get() const override;
	private:
		Inventory* _inventory;
		Item* _item;
	};
}