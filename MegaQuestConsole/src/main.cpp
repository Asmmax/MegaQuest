#include "Config/SettingsLoader.hpp"
#include "Game/GameLoop.hpp"
#include "Containers/GlobalContext.hpp"
#include "Quests/QuestTarget.hpp"

DECLARE_CONTAINER(IO::InputHandler)

int main()
{
    Config::SettingsLoader::Load("config.json");

    auto inputHandler = GlobalContext::GetContainer<IO::InputHandler>()->Get();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
