#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	class IInput
	{
	public:
		virtual ~IInput() = default;
		virtual QuestCore::TextString GetString() const = 0;
	};
}