#include "Config/SettingsLoader.hpp"
#include "Game/GameLoop.hpp"
#include "Containers/Context.hpp"
#include "Containers/ContextManager.hpp"
#include "Quests/QuestTarget.hpp"

int main()
{
    Config::SettingsLoader::Load("config.json");

    auto inputHandler = ContextManager::Instance().GetContext().GetContainer<IO::InputHandler>()->Get();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
