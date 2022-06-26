#pragma once
#include <memory>

namespace QuestCore
{
	class Item;
	class Inventory;

	/// @serializable @unique @abstract
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
		InventoryValue(const std::weak_ptr<Item>& item, const std::weak_ptr<Inventory>& inventory);
		virtual int Get() const override;
	private:
		std::weak_ptr<Inventory> _inventory;
		std::weak_ptr<Item> _item;
	};
}