#pragma once
#include "TextString.hpp"
#include <memory>

namespace QuestCore
{
	class IParagraph;

	class IRoom
	{
	public:
		virtual ~IRoom() = default;

		virtual const TextString& GetName() const = 0;
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const = 0;
	};
}
