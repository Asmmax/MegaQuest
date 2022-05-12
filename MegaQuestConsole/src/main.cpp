#include "Config/Settings.hpp"
#include "Factories/JsonQuestFactory.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleOutput.hpp"
#include "Model.hpp"
#include "InputHandler.hpp"

#include <iostream>

int main()
{
    auto& settings = Config::Settings::Instance();
    auto questFactory = std::make_shared<JsonQuestFactory>(settings.GetResourcePath() + "testquest.json");

    auto output = std::make_shared<IO::ConsoleOutput>();
    auto model = std::make_shared<Model>(output, questFactory);

    auto input = std::make_shared<IO::ConsoleInput>();
    auto inputHandler = std::make_shared<InputHandler>(input, output, model);

    Game::GameLoop game(inputHandler);
    return game.Run();
}
