#include "Game/GameLoop.hpp"
#include "Game/Events.hpp"
#include "IO/InputHandler.hpp"

using namespace Game;

GameLoop::GameLoop(IO::InputHandler* inputHandler) :
    _inputHandler(inputHandler)
{
    Game::Events::Quit.Subscribe([this]() {Quit(); });
}

void GameLoop::Update()
{
	_inputHandler->Handle();
}

void GameLoop::Init()
{
    _inputHandler->Init();
}

int GameLoop::Run()
{
    _isStoped = false;
    Init();
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
