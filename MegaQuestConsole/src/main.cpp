#include "Config/Settings.hpp"
#include "Factories/JsonQuestFactory.hpp"
#include "Player/PlayerController.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleView.hpp"
#include <iostream>

int main()
{
    auto& settings = Config::Settings::Instance();
    auto questFactory = std::make_shared<JsonQuestFactory>(settings.GetResourcePath() + "testquest.json");
    auto controller = std::make_shared<Player::PlayerController>(questFactory->GetQuest());

    Game::GameLoop game;
    auto input = std::make_shared<IO::ConsoleInput>(game, controller);
    auto view = std::make_shared<IO::ConsoleView>(input->GetInstructions());
    controller->SetTextView(view);
    game.SetInputHandler(input);

    return game.Run();
}
