#include "DIAssets.hpp"
#include "Game/GameLoop.hpp"
#include "Quests/QuestTarget.hpp"

#include "IO/Logger.hpp"

int main()
{
    Configurator container;
    container.Load("config.json");

    IO::Logger::Init(container.GetContext().GetContainer<IO::Logger>()->Get());

    auto inputHandler = container.GetContext().GetContainer<IO::InputHandler>()->Get();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
