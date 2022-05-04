#pragma once
#include "TextString.hpp"

namespace QuestCore
{
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual void Do() = 0;
	};
}
