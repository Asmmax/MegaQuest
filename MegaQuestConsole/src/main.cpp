#include "Player/PlayerInventory.hpp"
#include "Factories/TestRoadFactory.hpp"
#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleView.hpp"
#include <iostream>

int main()
{
    auto inventory = std::make_shared<Player::PlayerInventory>();
    auto roomFactory = std::make_shared<TestRoadFactory>(inventory);
    auto controller = std::make_shared<Player::PlayerController>(roomFactory->GetRoom(), inventory);

    Game::GameLoop game;
    auto input = std::make_shared<IO::ConsoleInput>(game, controller);
    auto view = std::make_shared<IO::ConsoleView>(input->GetInstructions());
    controller->SetTextView(view);
    game.SetInputHandler(input);

    return game.Run();
}
