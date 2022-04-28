#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class IParagraph;

	class IRoom
	{
	public:
		virtual ~IRoom() = default;

		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const = 0;
		virtual std::vector<std::string> GetHotKeys() const = 0;
	};
}
