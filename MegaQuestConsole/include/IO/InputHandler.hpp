#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	class IInput;
	class IOutput;
	class CommandManager;
	class Model;
}

namespace IO
{
	class InputHandler
	{
	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(Game::IInput* input, Game::IOutput* output, Game::CommandManager* commandManager, Game::Model* model);
		void Init();
		void Handle();

	private:
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		Game::IInput* _input;
		Game::IOutput* _output;
		Game::Model* _model;
		Game::CommandManager* _commandManager;
	};
}
