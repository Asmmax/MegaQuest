#pragma once
#include "Factories/IRoomFactory.hpp"

class TestRoadFactory : public QuestCore::IRoomFactory
{
public:
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;
};
