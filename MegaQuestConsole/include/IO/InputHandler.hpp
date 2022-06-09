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
	class IDialog;
}

namespace IO
{
	class QuitCommand : public Game::VoidCommand
	{
	public:
		virtual void Run() override;
	};

	class DialogVoidCommand : public Game::VoidCommand
	{
		using DialogPtr = std::shared_ptr<Game::IDialog>;
	public:
		DialogVoidCommand(const DialogPtr& dialog, const std::string& key);
		virtual void Run() override;
	private:
		DialogPtr _dialog;
		std::string _key;
	};

	class DialogIntCommand : public Game::IntCommand
	{
		using DialogPtr = std::shared_ptr<Game::IDialog>;
	public:
		DialogIntCommand(const DialogPtr& dialog);
		virtual void Run(int arg) override;
	private:
		DialogPtr _dialog;
	};

	class InputHandler
	{
		using InputPtr = std::shared_ptr<Game::IInput>;
		using OutputPtr = std::shared_ptr<Game::IOutput>;
		using DialogPtr = std::shared_ptr<Game::IDialog>;
		using Command = std::function<void()>;
		using CommandPtr = std::shared_ptr<Command>;

	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(const InputPtr& input, const OutputPtr& output, const DialogPtr& dialog);
		void Handle();

	private:
		CommandPtr GetCommand(const std::string& command);
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		InputPtr _input;
		OutputPtr _output;
		std::map<std::string, CommandPtr> _toCommands;
	};
}
