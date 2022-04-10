#include "Player\PlayerInventory.hpp"

using namespace Player;

void PlayerInventory::PutMoney(int money)
{
    _money += money;
}

void PlayerInventory::ThrowMoney(int money)
{
    _money = std::max(_money - money, 0);
}

void PlayerInventory::PutThing(const std::string& thing)
{
    _items.emplace_back(thing);
}

void PlayerInventory::ThrowThing(const std::string& thing)
{
    auto foundThing = std::find(_items.begin(), _items.end(), thing);
    if (foundThing != _items.end()) {
        _items.erase(foundThing);
    }
}

std::string PlayerInventory::GetContains()
{
    std::string containsString = "У вас " + std::to_string(_money) + " монет.\n";
    int itemCount = static_cast<int>(_items.size());

    if (itemCount == 1)
        containsString += "В сумке лежит " + _items[0] + ".\n";
    else if (itemCount > 1)
    {
        containsString += "В сумке лежат ";

        for (auto itemIt = _items.begin(); itemIt != _items.end(); itemIt++) {
            if (itemIt != _items.begin()) {
                containsString += ", ";
            }
            containsString += *itemIt;
        }

        containsString += ".\n";
    }

    return containsString;
}
