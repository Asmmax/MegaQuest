#include "Inventory.hpp"
#include "ItemInfo.hpp"

using namespace QuestCore;

void Inventory::PutItem(const ItemInfoPtr& item, int count)
{
    auto res = _items.emplace(item, count);
    if (!res.second) {
        res.first->second += count;
    }
}

void Inventory::ThrowItem(const ItemInfoPtr& item, int count)
{
    auto foundItemIt = _items.find(item);
    if (foundItemIt == _items.end()) {
        return;
    }

    foundItemIt->second = std::max(foundItemIt->second - count, 0);
    if (foundItemIt->second == 0 && !foundItemIt->first->IsNullable()) {
        _items.erase(foundItemIt);
    }
}

std::map<Inventory::ItemInfoPtr, int> Inventory::GetNullableItems() const
{
    std::map<ItemInfoPtr, int> nullableItems;
    for (auto& item : _items) {
        if (item.first->IsNullable()) {
            nullableItems.insert(item);
        }
    }
    return nullableItems;
}

std::map<Inventory::ItemInfoPtr, int> Inventory::GetItems() const
{
    auto items(_items);
    auto nullableItems = GetNullableItems();
    for (auto& removeItem : nullableItems) {
        items.erase(removeItem.first);
    }
    return items;
}
