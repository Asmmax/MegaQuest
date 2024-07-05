#include "Actions/Transfer.hpp"
#include "Item.hpp"

using namespace QuestCore;

Transfer::Transfer(Inventory* source, Inventory* target, const std::vector<ItemRecord>& items) :
    _source(source),
    _target(target),
    _things(items)
{
}

void Transfer::Do()
{
    std::vector<ItemRecord> things = BoundThingsBy(_source);
    if (_source) {
        for (auto& thing : things) {
            _source->ThrowItem(thing.item, thing.count);
        }
    }

    if (_target) {
        for (auto& thing : things) {
            _target->PutItem(thing.item, thing.count);
        }
    }
}

void Transfer::AddThings(Item* thing, int count)
{
    ItemRecord item{ thing, count };
    _things.push_back(item);
}

std::vector<ItemRecord> Transfer::BoundThingsBy(Inventory* inventory)
{
    std::vector<ItemRecord> things(_things);
    if (_source) {
        auto& items = _source->GetItems();
        for (auto& thing : things) {
            auto itemIt = items.find(thing.item);
            if (itemIt == items.end()) {
                thing.count = 0;
            }
            else if (itemIt->second < thing.count) {
                thing.count = itemIt->second;
            }
        }
    }
    return things;
}
