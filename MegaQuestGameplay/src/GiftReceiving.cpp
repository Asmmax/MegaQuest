#include "GiftReceiving.hpp"
#include "Inventory.hpp"
#include "ItemInfo.hpp"

using namespace QuestCore;

GiftReceiving::GiftReceiving(const std::string& name, const std::shared_ptr<Inventory>& inventory):
	_name(name),
    _inventory(inventory)
{
}

std::string GiftReceiving::GetName() const
{
	return _name;
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

void GiftReceiving::AddThings(const ItemInfoPtr& thing, int count)
{
    _things.emplace_back(thing, count);
    if (thing->IsNullable()) {
        _inventory->PutItem(thing, 0);
    }
}
