#pragma once
#include "Game/Commands/IntCommand.hpp"
#include "Game/Commands/VoidCommand.hpp"
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
	class QuitCommand : public Game::VoidCommand
	{
	public:
		virtual void Run() override;
	};

	class ModelVoidCommand : public Game::VoidCommand
	{
		using ModelPtr = std::shared_ptr<Game::Model>;
	public:
		ModelVoidCommand(const ModelPtr& model, const std::string& key);
		virtual void Run() override;
	private:
		ModelPtr _model;
		std::string _key;
	};

	class ModelIntCommand : public Game::IntCommand
	{
		using ModelPtr = std::shared_ptr<Game::Model>;
	public:
		ModelIntCommand(const ModelPtr& model);
		virtual void Run(int arg) override;
	private:
		ModelPtr _model;
	};

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
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		InputPtr _input;
		OutputPtr _output;
		ModelPtr _model;
		std::map<std::string, CommandPtr> _toCommands;
	};
}
