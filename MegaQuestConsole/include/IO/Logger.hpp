#pragma once

#include "TextString.hpp"
#include <string>
#include <memory>

namespace Game
{
	class IOutput;
}

namespace IO
{
	class Logger
	{
	public:
		static Logger& Instance();
		void Init(Game::IOutput* output);
		void Log(const QuestCore::TextString& text);

	private:
		Game::IOutput* _output;
	};
}
