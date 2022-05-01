#include "Inventory.hpp"
#include "Item.hpp"

using namespace QuestCore;

void Inventory::PutItem(const ItemPtr& item, int count)
{
    auto res = _items.emplace(item, count);
    if (!res.second) {
        res.first->second += count;
    }
}

void Inventory::ThrowItem(const ItemPtr& item, int count)
{
    auto foundItemIt = _items.find(item);
    if (foundItemIt == _items.end()) {
        return;
    }

    foundItemIt->second = std::max(foundItemIt->second - count, 0);
    if (!foundItemIt->first->IsNullable() && foundItemIt->second == 0) {
        _items.erase(foundItemIt);
    }
}
