#pragma once
#include <memory>

namespace QuestCore
{
	class IRoom;

	class IRoomFactory
	{
	public:
		virtual ~IRoomFactory() = default;
		virtual std::shared_ptr<IRoom> GetRoom() = 0;
	};
}
