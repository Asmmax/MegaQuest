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
	/// @serializable @shared logger
	class Logger
	{
		using OutputPtr = std::shared_ptr<Game::IOutput>;

	public:
		static void Init(const std::shared_ptr<Logger>& logger);
		static Logger& Instance();
		/// @inject
		void SetOutput(const OutputPtr& output);
		void Log(const QuestCore::TextString& text);

	private:
		OutputPtr _output;
		static std::shared_ptr<Logger> _instance;
	};
}
