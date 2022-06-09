#include "IO/InputHandler.hpp"
#include "Game/IInput.hpp"
#include "Game/IOutput.hpp"
#include "Game/CommandManager.hpp"

#include <iostream>

using namespace Game;
using namespace IO;

InputHandler::InputHandler(const IInput::Ptr& input, const IOutput::Ptr& output):
	_input(input),
	_output(output)
{
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
	CommandManager::Instance().Run(command, args);
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
