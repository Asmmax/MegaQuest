#include "Inventory.hpp"
#include "Item.hpp"

using namespace QuestCore;

Inventory::Inventory(const QuestHeaderPtr& quest, const std::vector<ItemRecord>& items):
    QuestInitable(quest)
{
    for (auto& item : items) {
        _initItems.emplace(item.item, item.count);
    }
}

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
}

void Inventory::Init()
{
    _items.clear();
    for (auto& item : _initItems) {
        _items.emplace(item.first, item.second);
    }
}
