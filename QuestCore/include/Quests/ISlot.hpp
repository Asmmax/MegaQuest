#pragma once

namespace QuestCore
{
	/// @serializable @shared slots @abstract
	class ISlot
	{
	public:
		virtual ~ISlot() = default;
		virtual void Update() = 0;
	};
}
