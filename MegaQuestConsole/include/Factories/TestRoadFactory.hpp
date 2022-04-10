#pragma once
#include "Factories/IRoomFactory.hpp"

namespace QuestCore
{
	class IInventory;
}

class TestRoadFactory : public QuestCore::IRoomFactory
{
public:
	TestRoadFactory(const std::shared_ptr<QuestCore::IInventory>& playerInventory);
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;

private:
	std::shared_ptr<QuestCore::IInventory> _playerInventory;
};
