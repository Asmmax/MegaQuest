#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	/// @serializable @shared inputs @abstract
	class IInput
	{
	public:
		using Ptr = std::shared_ptr<IInput>;

		virtual ~IInput() = default;
		virtual QuestCore::TextString GetString() const = 0;
	};
}