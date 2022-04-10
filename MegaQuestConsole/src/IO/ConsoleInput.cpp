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
	return "���������� � ���� �������������� ����� �������� ������ � ������� inventory(i) � quit(q).\n";
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
            std::cout << "������� ����� ����� ������ �� ������������." << std::endl;
        }

    }
    catch (const std::invalid_argument& /*ex*/) {
        std::cout << "����� ����� ���� ������ ������, Inventory ��� Quit." << std::endl;
    }
}
