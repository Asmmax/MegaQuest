#include "Config/Settings.hpp"
#include "Factories/JsonQuestFactory.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleOutput.hpp"
#include "IO/InputHandler.hpp"
#include "Factories/DialogFactory.hpp"
#include "IO/Logger.hpp"
#include "Game/IDialog.hpp"
#include "Factories/CommandsFactory.hpp"

#include <iostream>

int main()
{
    auto& settings = Config::Settings::Instance();
    auto rootFactory = std::make_shared<JsonQuestFactory>(settings.GetQuestPath());

    auto output = std::make_shared<IO::ConsoleOutput>();
    IO::Logger::Instance().Init(output);
    auto dialogFactory = std::make_shared<DialogFactory>(settings.GetDialogsPath(), output, rootFactory);
    auto model = dialogFactory->GetRootDialog();
    if (model) {
        model->Init();
        model->Update();
    }

    auto commandsFactory = std::make_shared<CommandsFactory>(settings.GetCommandsPath(), dialogFactory);
    auto commandManager = commandsFactory->GetCommandManager();

    auto input = std::make_shared<IO::ConsoleInput>();
    auto inputHandler = std::make_shared<IO::InputHandler>(input, output, commandManager);

    Game::GameLoop game(inputHandler);
    return game.Run();
}
