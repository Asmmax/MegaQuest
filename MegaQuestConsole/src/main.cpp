﻿#include "Config/SettingsLoader.hpp"
#include "Game/GameLoop.hpp"
#include "Containers/Context.hpp"
#include "Quests/QuestTarget.hpp"

int main()
{
    Config::SettingsLoader::Load("config.json");

    auto inputHandler = Context::Global().GetContainer<IO::InputHandler>()->Get();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
