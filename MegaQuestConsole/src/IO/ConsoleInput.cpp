#include "IO/ConsoleInput.hpp"
#include "Game/GameLoop.hpp"
#include "Player/PlayerController.hpp"

#include <iostream>

using namespace IO;
using namespace QuestCore;

ConsoleInput::ConsoleInput(Game::GameLoop& gameLoop, const std::shared_ptr<Player::PlayerController>& playerController):
	_gameLoop(gameLoop),
	_playerController(playerController)
{
}

TextString ConsoleInput::GetInstructions()
{
	return TextString::FromUtf8(u8"”правление в игре осуществл€етс€ через цифровые кнопки и команды inventory(i) и quit(q).\n");
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
#ifdef _WIN32
            std::wcout << L"¬водить цифру можно только из предложенных." << std::endl;
#else
            std::cout << "¬водить цифру можно только из предложенных." << std::endl;
#endif // _WIN32
        }

    }
    catch (const std::invalid_argument& /*ex*/) {
#ifdef _WIN32
        std::wcout << L"ќтвет может быть только цифрой, Inventory или Quit." << std::endl;
#else
        std::cout << "ќтвет может быть только цифрой, Inventory или Quit." << std::endl;
#endif // _WIN32
    }
}
