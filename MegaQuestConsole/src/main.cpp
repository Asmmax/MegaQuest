#include "Config/SettingsLoader.hpp"
#include "Game/GameLoop.hpp"
#include "IO/ConsoleInput.hpp"
#include "IO/ConsoleOutput.hpp"
#include "IO/InputHandler.hpp"
#include "IO/Logger.hpp"
#include "Game/Model.hpp"

#include "Containers/GlobalContext.hpp"

int main()
{
    Config::SettingsLoader::Load("config.json");

    auto output = std::make_shared<IO::ConsoleOutput>();
    IO::Logger::Instance().Init(output);
    auto model = GlobalContext::GetContainer<Game::Model>()->Get();
    model->SetOutput(output);
    if (model) {
        model->Init();
        model->Update();
    }

    auto commandManager = GlobalContext::GetContainer<Game::CommandManager>()->Get();

    auto input = std::make_shared<IO::ConsoleInput>();
    auto inputHandler = std::make_shared<IO::InputHandler>(input, output, commandManager);

    Game::GameLoop game(inputHandler);
    return game.Run();
}
