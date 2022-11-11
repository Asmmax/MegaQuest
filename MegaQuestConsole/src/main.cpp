#include "DIAssets.hpp"
#include "Game/GameLoop.hpp"
#include "Quests/QuestTarget.hpp"

int main()
{
    SettingsLoader::Load("config.json");

    auto inputHandler = ContextManager::Instance().GetContext().GetContainer<IO::InputHandler>()->Get();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
