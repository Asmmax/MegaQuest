#include "IO/InputHandler.hpp"
#include "Game/IInput.hpp"
#include "Game/IOutput.hpp"
#include "Game/Model.hpp"
#include "Game/Events.hpp"
#include "Game/CommandManager.hpp"
#include "Game/Commands/AliasCommand.hpp"

#include <iostream>

using namespace Game;
using namespace IO;

void QuitCommand::Run()
{
	Game::Events::Quit.Send();
}

ModelVoidCommand::ModelVoidCommand(const ModelPtr& model, const std::string& key):
	_model(model),
	_key(key)
{
}

void ModelVoidCommand::Run()
{
	_model->Handle(_key);
}

ModelIntCommand::ModelIntCommand(const ModelPtr& model) :
	IntCommand(QuestCore::TextString::FromUtf8("Вводить можно только цифру из предложенных!")),
	_model(model)
{
}

void ModelIntCommand::Run(int arg)
{
	_model->Handle(arg - 1);
}



InputHandler::InputHandler(const IInput::Ptr& input, const IOutput::Ptr& output, const Model::Ptr& model):
	_input(input),
	_output(output),
	_model(model)
{
	auto intro = QuestCore::TextString::FromUtf8(u8"Добро пожаловать в квест! Вы можете ввести Quit, Inventory или цифры.");
	_output->WriteLn(intro);

	CommandManager::Instance().Register("quit", std::make_shared<QuitCommand>());
	CommandManager::Instance().Register("q", std::make_shared<Game::AliasCommand>("quit"));
	CommandManager::Instance().Register("Quit", std::make_shared<Game::AliasCommand>("quit"));
	CommandManager::Instance().Register("Q", std::make_shared<Game::AliasCommand>("quit"));

	CommandManager::Instance().Register("inventory", std::make_shared<ModelVoidCommand>(_model, "inventory"));
	CommandManager::Instance().Register("i", std::make_shared<Game::AliasCommand>("inventory"));
	CommandManager::Instance().Register("Inventory", std::make_shared<Game::AliasCommand>("inventory"));
	CommandManager::Instance().Register("I", std::make_shared<Game::AliasCommand>("inventory"));

	CommandManager::Instance().Register("", std::make_shared<ModelIntCommand>(_model));

	_model->Update();
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
