#include "Game/GameLoop.hpp"
#include "InputHandler.hpp"
#include "Events.hpp"

using namespace Game;

GameLoop::GameLoop(const InputHandler::Ptr& inputHandler):
    _inputHandler(inputHandler)
{
    GameEvents::Quit.Subscribe([this]() {Quit(); });
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
