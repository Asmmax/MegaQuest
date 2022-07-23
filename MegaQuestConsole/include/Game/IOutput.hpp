#pragma once
#include <memory>

namespace QuestCore
{
	class TextString;
}

namespace Game
{
	/// @serializable @shared outputs @abstract
	class IOutput
	{
	public:
		using Ptr = std::shared_ptr<IOutput>;

		virtual ~IOutput() = default;
		virtual void Write(const QuestCore::TextString& text) = 0;
		virtual void WriteLn(const QuestCore::TextString& text) = 0;
		virtual void WriteLn() = 0;
	};
}
