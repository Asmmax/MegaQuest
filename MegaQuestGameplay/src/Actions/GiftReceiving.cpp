#include "Actions/GiftReceiving.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace QuestCore;

GiftReceiving::GiftReceiving(const std::shared_ptr<Inventory>& inventory):
    _inventory(inventory)
{
}

void GiftReceiving::Do()
{
    if (!_inventory) {
        return;
    }

    for (auto& thing : _things) {
        _inventory->PutItem(thing.first, thing.second);
    }
}

void GiftReceiving::AddThings(const ItemPtr& thing, int count)
{
    _things.emplace_back(thing, count);
}
