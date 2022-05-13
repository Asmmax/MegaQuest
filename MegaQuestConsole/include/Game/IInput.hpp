#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	class IInput
	{
	public:
		using Ptr = std::shared_ptr<IInput>;

		virtual ~IInput() = default;
		virtual QuestCore::TextString GetString() const = 0;
	};
}