#pragma once
#include "TextString.hpp"

namespace QuestCore
{
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual TextString GetName() const = 0;
		virtual void Do() = 0;
	};
}
