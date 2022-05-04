#include "Actions/Transfer.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace QuestCore;

Transfer::Transfer(const std::shared_ptr<Inventory>& source, const std::shared_ptr<Inventory>& target):
    _source(source),
    _target(target)
{
}

void Transfer::Do()
{
    std::vector<ItemQuery> things = BoudThingsBy(_source);
    if (_source) {
        for (auto& thing : things) {
            _source->ThrowItem(thing.first, thing.second);
        }
    }

    if (_target) {
        for (auto& thing : things) {
            _target->PutItem(thing.first, thing.second);
        }
    }
}

void Transfer::AddThings(const ItemPtr& thing, int count)
{
    _things.emplace_back(thing, count);
}

std::vector<Transfer::ItemQuery> Transfer::BoudThingsBy(const std::shared_ptr<Inventory>& inventory)
{
    std::vector<ItemQuery> things(_things);
    if (_source) {
        auto& items = _source->GetItems();
        for (auto& thing : things) {
            auto itemIt = items.find(thing.first);
            if (itemIt == items.end()) {
                thing.second = 0;
            }
            else if (itemIt->second < thing.second) {
                thing.second = itemIt->second;
            }
        }
    }
    return things;
}
