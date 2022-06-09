#include "IO/InputHandler.hpp"
#include "Game/IInput.hpp"
#include "Game/IOutput.hpp"
#include "Game/IDialog.hpp"
#include "Game/Events.hpp"
#include "Game/CommandManager.hpp"
#include "Game/Commands/AliasCommand.hpp"
#include "Game/ButtonList.hpp"

#include <iostream>

using namespace Game;
using namespace IO;

void QuitCommand::Run()
{
	Game::Events::Quit.Send();
}

DialogVoidCommand::DialogVoidCommand(const DialogPtr& dialog, const std::string& key):
	_dialog(dialog),
	_key(key)
{
}

void DialogVoidCommand::Run()
{
	if (auto inventoryButtons = _dialog->GetButtonList(_key)) {
		inventoryButtons->Do();
	}
}

DialogIntCommand::DialogIntCommand(const DialogPtr& dialog) :
	IntCommand(QuestCore::TextString::FromUtf8("Вводить можно только цифру из предложенных!")),
	_dialog(dialog)
{
}

void DialogIntCommand::Run(int arg)
{
	if (auto defaultButtons = _dialog->GetButtonList()) {
		defaultButtons->Do(arg - 1);
	}
}



InputHandler::InputHandler(const IInput::Ptr& input, const IOutput::Ptr& output, const IDialog::Ptr& dialog):
	_input(input),
	_output(output)
{
	auto intro = QuestCore::TextString::FromUtf8(u8"Добро пожаловать в квест! Вы можете ввести Quit, Inventory или цифры.");
	_output->WriteLn(intro);

	CommandManager::Instance().Register("quit", std::make_shared<QuitCommand>());
	CommandManager::Instance().Register("q", std::make_shared<Game::AliasCommand>("quit"));
	CommandManager::Instance().Register("Quit", std::make_shared<Game::AliasCommand>("quit"));
	CommandManager::Instance().Register("Q", std::make_shared<Game::AliasCommand>("quit"));

	CommandManager::Instance().Register("inventory", std::make_shared<DialogVoidCommand>(dialog, "inventory"));
	CommandManager::Instance().Register("i", std::make_shared<Game::AliasCommand>("inventory"));
	CommandManager::Instance().Register("Inventory", std::make_shared<Game::AliasCommand>("inventory"));
	CommandManager::Instance().Register("I", std::make_shared<Game::AliasCommand>("inventory"));

	CommandManager::Instance().Register("", std::make_shared<DialogIntCommand>(dialog));

	dialog->Update();
}

InputHandler::CommandPtr InputHandler::GetCommand(const std::string& command)
{
	auto foundIt = _toCommands.find(command);
	if (foundIt == _toCommands.end()) {
		return nullptr;
	}

	return foundIt->second;
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
	auto strs = command.SplitBy(QuestCore::TextString::FromUtf8(" "));
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
