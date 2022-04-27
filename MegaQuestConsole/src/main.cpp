#include "Config/Settings.hpp"
#include "Factories/JsonRoomFactory.hpp"
#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleView.hpp"
#include <iostream>

int main()
{
    auto& settings = Config::Settings::Instance();
    auto roomFactory = std::make_shared<JsonRoomFactory>(settings.GetResourcePath() + "testquest.json");
    auto controller = std::make_shared<Player::PlayerController>(roomFactory->GetRoom());

    Game::GameLoop game;
    auto input = std::make_shared<IO::ConsoleInput>(game, controller);
    auto view = std::make_shared<IO::ConsoleView>(input->GetInstructions());
    controller->SetTextView(view);
    game.SetInputHandler(input);

    return game.Run();
}
