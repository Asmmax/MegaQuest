#pragma once
#include "IRoomFactory.hpp"

class TestRoadFactory : public QuestCore::IRoomFactory
{
public:
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;
};
