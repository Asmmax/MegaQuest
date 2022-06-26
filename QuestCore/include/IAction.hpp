#pragma once
#include "TextString.hpp"

namespace QuestCore
{
	/// @serializable @shared(actions) @abstract
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual void Do() = 0;
	};
}
