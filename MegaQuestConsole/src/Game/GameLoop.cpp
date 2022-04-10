#include "Game/GameLoop.hpp"
#include "Game/IInputHandler.hpp"

using namespace Game;

void GameLoop::SetInputHandler(const std::shared_ptr<IInputHandler>& inputHandler)
{
	_inputHandler = inputHandler;
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
