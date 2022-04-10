#include "IO/ConsoleInput.hpp"
#include "Game/GameLoop.hpp"
#include "Player/PlayerController.hpp"

#include <iostream>

using namespace IO;

ConsoleInput::ConsoleInput(Game::GameLoop& gameLoop, const std::shared_ptr<Player::PlayerController>& playerController):
	_gameLoop(gameLoop),
	_playerController(playerController)
{
}

std::string ConsoleInput::GetInstructions()
{
	return "”правление в игре осуществл€етс€ через цифровые кнопки и команды inventory(i) и quit(q).\n";
}

void ConsoleInput::Handle()
{
    std::string answer;
    std::getline(std::cin, answer);

    if (answer == "Quit" || answer == "quit" || answer == "Q" || answer == "q")
    {
        _gameLoop.Quit();
        return;
    }

    if (answer == "Inventory" || answer == "inventory" || answer == "I" || answer == "i")
    {
        _playerController->OpenInventory();
        return;
    }

    try 
    {
        int answerID = std::stoi(answer);

        try
        {
            _playerController->DoCommand(answerID);
        }
        catch (const Player::AnswerNotExsistExeption& /*ex*/)
        {
            std::cout << "¬водить цифру можно только из предложенных." << std::endl;
        }

    }
    catch (const std::invalid_argument& /*ex*/) {
        std::cout << "ќтвет может быть только цифрой, Inventory или Quit." << std::endl;
    }
}
