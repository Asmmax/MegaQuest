#pragma once
#include "Game/IOutput.hpp"

namespace IO
{
	/// @serializable
	class ConsoleOutput : public Game::IOutput
	{
	public:
		ConsoleOutput();
		virtual void Write(const QuestCore::TextString& text) override;
		virtual void WriteLn(const QuestCore::TextString& text) override;
		virtual void WriteLn() override;
	};
}
