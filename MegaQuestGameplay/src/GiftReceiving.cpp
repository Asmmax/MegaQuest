#include "GiftReceiving.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace QuestCore;

GiftReceiving::GiftReceiving(const TextString& name, const std::shared_ptr<Inventory>& inventory):
	_name(name),
    _inventory(inventory)
{
}

TextString GiftReceiving::GetName() const
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

void GiftReceiving::AddThings(const ItemPtr& thing, int count)
{
    _things.emplace_back(thing, count);
}
