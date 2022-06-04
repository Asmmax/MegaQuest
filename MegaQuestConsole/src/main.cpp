#include "Config/Settings.hpp"
#include "Factories/JsonQuestFactory.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleOutput.hpp"
#include "IO/InputHandler.hpp"
#include "Game/Model.hpp"
#include "Factories/DialogFactory.hpp"

#include <iostream>

int main()
{
    auto& settings = Config::Settings::Instance();
    auto rootFactory = std::make_shared<JsonQuestFactory>(settings.GetQuestPath());

    auto output = std::make_shared<IO::ConsoleOutput>();
    auto dialogFactory = std::make_shared<DialogFactory>(output, rootFactory);
    auto dialogs = dialogFactory->GetDialogs();
    auto model = std::make_shared<Game::Model>(dialogs);

    auto input = std::make_shared<IO::ConsoleInput>();
    auto inputHandler = std::make_shared<IO::InputHandler>(input, output, model);

    Game::GameLoop game(inputHandler);
    return game.Run();
}
