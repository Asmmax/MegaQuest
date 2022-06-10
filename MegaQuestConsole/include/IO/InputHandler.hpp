#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	class IInput;
	class IOutput;
	class CommandManager;
}

namespace IO
{
	class InputHandler
	{
		using InputPtr = std::shared_ptr<Game::IInput>;
		using OutputPtr = std::shared_ptr<Game::IOutput>;
		using CommandManagerPtr = std::shared_ptr<Game::CommandManager>;

	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(const InputPtr& input, const OutputPtr& output, const CommandManagerPtr& commandManager);
		void Handle();

	private:
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		InputPtr _input;
		OutputPtr _output;
		CommandManagerPtr _commandManager;
	};
}
