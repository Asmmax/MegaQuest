#include "GiftReceiving.hpp"
#include "IInventory.hpp"

using namespace QuestCore;

QuestCore::GiftReceiving::GiftReceiving(const std::string& name):
	_name(name),
    _money(0)
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

    _inventory->PutMoney(_money);

    for (auto& thing : _things) {
        _inventory->PutThing(thing);
    }
}
