#include "IO/InputHandler.hpp"
#include "Game/IInput.hpp"
#include "Game/IOutput.hpp"
#include "Game/CommandManager.hpp"
#include "Game/Model.hpp"

#include <iostream>

using namespace Game;
using namespace IO;

InputHandler::InputHandler(const Game::IInput::Ptr& input, const IOutput::Ptr& output, const CommandManagerPtr& commandManager, const ModelPtr& model):
	_input(input),
	_output(output),
	_commandManager(commandManager),
	_model(model)
{
}

void InputHandler::Init()
{
	_model->Reset();
}

void InputHandler::Handle()
{
	auto answer = _input->GetString();
	if (answer.IsEmpty()) {
		return;
	}

	_output->WriteLn();

	auto args = Parse(answer);
	if (args.empty()) {
		return;
	}

	std::string command = args.front();
	args.erase(args.begin());
	_commandManager->Run(command, args);
}

std::vector<std::string> InputHandler::Parse(const QuestCore::TextString& command)
{
	auto strs = command.SplitBy(QuestCore::TextString::FromUtf8(u8" "));
	std::vector<std::string> args;
	for (auto& str : strs) {
		if (!str.IsEmpty()) {
			args.push_back(str.ToUtf8());
		}
	}

	if (args.empty()) {
		return args;
	}

	if (std::isdigit(args.front().front())) {
		args.insert(args.begin(), "");
	}

	return args;
}
