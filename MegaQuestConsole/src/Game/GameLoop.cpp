#include "Game/GameLoop.hpp"
#include "Game/Events.hpp"
#include "IO/InputHandler.hpp"

using namespace Game;

GameLoop::GameLoop(const IO::InputHandler::Ptr & inputHandler) :
    _inputHandler(inputHandler)
{
    Game::Events::Quit.Subscribe([this]() {Quit(); });
}

void GameLoop::Update()
{
	_inputHandler->Handle();
}

int GameLoop::Run()
{
    _isStoped = false;
    while (!_isStoped)
    {
        Update();
    }

    return 0;
}

void GameLoop::Quit()
{
    _isStoped = true;
}
