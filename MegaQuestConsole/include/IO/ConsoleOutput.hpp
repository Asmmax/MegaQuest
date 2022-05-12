#pragma once
#include "IOutput.hpp"

namespace IO
{
	class ConsoleOutput : public IOutput
	{
	public:
		ConsoleOutput();
		virtual void Write(const QuestCore::TextString& text) override;
		virtual void WriteLn(const QuestCore::TextString& text) override;
		virtual void WriteLn() override;
	};
}
