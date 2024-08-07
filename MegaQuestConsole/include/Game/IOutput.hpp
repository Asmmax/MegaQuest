#pragma once
#include <memory>

namespace QuestCore
{
	class TextString;
}

namespace Game
{
	class IOutput
	{
	public:
		virtual ~IOutput() = default;
		virtual void Write(const QuestCore::TextString& text) = 0;
		virtual void WriteLn(const QuestCore::TextString& text) = 0;
		virtual void WriteLn() = 0;
	};
}
