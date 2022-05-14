#include "IO/InputHandler.hpp"
#include "Game/IInput.hpp"
#include "Game/IOutput.hpp"
#include "Game/Model.hpp"
#include "Game/Events.hpp"

#include <iostream>

using namespace Game;
using namespace IO;

InputHandler::InputHandler(const IInput::Ptr& input, const IOutput::Ptr& output, const Model::Ptr& model):
	_input(input),
	_output(output),
	_model(model)
{
	auto intro = QuestCore::TextString::FromUtf8(u8"Добро пожаловать в квест! Вы можете ввести Quit, Inventory или цифры.");
	_output->WriteLn(intro);

	CommandPtr quitCommand = std::make_shared<Command>([]() {
		Game::Events::Quit.Send(); 
		});
	_toCommands.emplace(u8"q", quitCommand);
	_toCommands.emplace(u8"Q", quitCommand);
	_toCommands.emplace(u8"quit", quitCommand);
	_toCommands.emplace(u8"Quit", quitCommand);

	CommandPtr inventoryCommand = std::make_shared<Command>([this]() {
		_model->OpenInventory(); 
		_model->Update();
		});
	_toCommands.emplace(u8"i", inventoryCommand);
	_toCommands.emplace(u8"I", inventoryCommand);
	_toCommands.emplace(u8"inventory", inventoryCommand);
	_toCommands.emplace(u8"Inventory", inventoryCommand);

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

	try
	{
		int answerID = std::stoi(answer.ToUtf8());
		bool res = _model->Handle(answerID - 1);
		if (res) {
			_model->Update();
		}
		else {
			auto error = QuestCore::TextString::FromUtf8(u8"Вводить можно только цифру из предложенных!");
			_output->WriteLn(error);
		}
	}
	catch (const std::invalid_argument& /*ex*/) {
		if (auto commandPtr = GetCommand(answer.ToUtf8())) {
			auto& command = *commandPtr;
			command();
		}
		else
		{
			auto error = QuestCore::TextString::FromUtf8(u8"Вводить можно только цифру, Quit или Inventory!");
			_output->WriteLn(error);
		}
	}
}
