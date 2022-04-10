#pragma once
#include "Game/IInputHandler.hpp"
#include <memory>
#include <string>

namespace Player
{
	class PlayerController;
}

namespace Game {
	class GameLoop;
}

namespace IO
{
	class ConsoleInput : public Game::IInputHandler
	{
	public:
        ConsoleInput(Game::GameLoop& gameLoop, const std::shared_ptr<Player::PlayerController>& playerController);
        std::string GetInstructions();
		void Handle();

	private:
		Game::GameLoop& _gameLoop;
		std::shared_ptr<Player::PlayerController> _playerController;
	};
}
