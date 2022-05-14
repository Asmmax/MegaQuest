#pragma once
#include <string>
#include <memory>
#include <map>
#include <functional>

namespace Game 
{
	class IInput;
	class IOutput;
	class Model;
}

namespace IO
{
	class InputHandler
	{
		using InputPtr = std::shared_ptr<Game::IInput>;
		using OutputPtr = std::shared_ptr<Game::IOutput>;
		using ModelPtr = std::shared_ptr<Game::Model>;
		using Command = std::function<void()>;
		using CommandPtr = std::shared_ptr<Command>;

	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(const InputPtr& input, const OutputPtr& output, const ModelPtr& model);
		void Handle();

	private:
		CommandPtr GetCommand(const std::string& command);

	private:
		InputPtr _input;
		OutputPtr _output;
		ModelPtr _model;
		std::map<std::string, CommandPtr> _toCommands;
	};
}
