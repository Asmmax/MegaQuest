#pragma once
#include <string>
#include <memory>

namespace QuestCore
{
	class IParagraph;

	class IRoom
	{
	public:
		virtual ~IRoom() = default;

		virtual const std::string& GetName() const = 0;
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const = 0;
	};
}
