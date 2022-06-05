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
		using OutputPtr = std::shared_ptr<Game::IOutput>;

	public:
		static Logger& Instance();
		void Init(const OutputPtr& output);
		void Log(const QuestCore::TextString& text);

	private:
		OutputPtr _output;
	};
}
