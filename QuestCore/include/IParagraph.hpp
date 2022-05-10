#pragma once
#include <memory>

namespace QuestCore
{
	class TextString;

	class IParagraph
	{
	public:
		using Ptr = std::shared_ptr<IParagraph>;

		virtual ~IParagraph() = default;

		virtual TextString GetText() const = 0;
	};
}
