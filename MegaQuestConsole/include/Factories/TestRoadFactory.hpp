#pragma once
#include "Factories/IRoomFactory.hpp"

namespace QuestCore
{
	class Inventory;
}

class TestRoadFactory : public QuestCore::IRoomFactory
{
public:
	TestRoadFactory(const std::shared_ptr<QuestCore::Inventory>& playerInventory);
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;

private:
	std::shared_ptr<QuestCore::Inventory> _playerInventory;
};
