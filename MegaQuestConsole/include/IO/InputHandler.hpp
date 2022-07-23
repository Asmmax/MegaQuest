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
	/// @serializable @shared inputHandler
	class InputHandler
	{
		using InputPtr = std::shared_ptr<Game::IInput>;
		using OutputPtr = std::shared_ptr<Game::IOutput>;
		using CommandManagerPtr = std::shared_ptr<Game::CommandManager>;
		using ModelPtr = std::shared_ptr<Game::Model>;

	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(const InputPtr& input, const OutputPtr& output, const CommandManagerPtr& commandManager, const ModelPtr& model);
		void Init();
		void Handle();

	private:
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		InputPtr _input;
		OutputPtr _output;
		ModelPtr _model;
		CommandManagerPtr _commandManager;
	};
}
