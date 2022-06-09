#include "Factories/DialogFactory.hpp"
#include "Game/SimpleDialog.hpp"
#include "Game/SwitchDialog.hpp"
#include "Factories/IRootFactory.hpp"
#include "Game/SimpleButtonList.hpp"

#include "Game/CommandManager.hpp"
#include "Game/Commands/AliasCommand.hpp"
#include "Game/Commands/QuitCommand.hpp"
#include "Game/Commands/ChoiceCommand.hpp"
#include "Game/Commands/ForceChoiceCommand.hpp"

DialogFactory::DialogFactory(const OutputPtr& output, const RootFactoryPtr& rootFactory):
    _isRed(false),
    _output(output),
    _rootFactory(rootFactory)
{
}

void DialogFactory::Read()
{
    if (_isRed) {
        return;
    }

    std::vector<Game::IDialog::Ptr> dialogs;

    auto paragraph = _rootFactory->GetRootParagraph("root");
    auto caseContainer = _rootFactory->GetRootCaseContainer("root");
    auto intro = QuestCore::TextString::FromUtf8(u8"Добро пожаловать в квест! Вы можете ввести Quit, Inventory или цифры.");
    auto dialog = std::make_shared<Game::SimpleDialog>(_output, paragraph, caseContainer, intro);

    auto buttonsError = QuestCore::TextString::FromUtf8(u8"Вводить можно только цифру из предложенных!");
    auto defaultButtonList = std::make_shared<Game::SimpleButtonList>(dialog, buttonsError);
    dialog->AddButtonList("", defaultButtonList);

    auto inventoryButtonList = std::make_shared<Game::SimpleButtonList>(dialog);
    dialog->AddButtonList("inventory", inventoryButtonList);

    dialogs.push_back(dialog);


    _dialog = std::make_shared<Game::SwitchDialog>(dialogs);

    Game::CommandManager::Instance().Register("quit", std::make_shared<Game::QuitCommand>());
    Game::CommandManager::Instance().Register("q", std::make_shared<Game::AliasCommand>("quit"));
    Game::CommandManager::Instance().Register("Quit", std::make_shared<Game::AliasCommand>("quit"));
    Game::CommandManager::Instance().Register("Q", std::make_shared<Game::AliasCommand>("quit"));

    Game::CommandManager::Instance().Register("inventory", std::make_shared<Game::ForceChoiceCommand>(_dialog, "inventory"));
    Game::CommandManager::Instance().Register("i", std::make_shared<Game::AliasCommand>("inventory"));
    Game::CommandManager::Instance().Register("Inventory", std::make_shared<Game::AliasCommand>("inventory"));
    Game::CommandManager::Instance().Register("I", std::make_shared<Game::AliasCommand>("inventory"));

    auto errorInt = QuestCore::TextString::FromUtf8(u8"Вводить можно только цифру, Quit или Inventory!");
    Game::CommandManager::Instance().Register("", std::make_shared<Game::ChoiceCommand>(_dialog, "", errorInt));

    _isRed = true;
}

Game::IDialog::Ptr DialogFactory::GetDialog()
{
    Read();
    return _dialog;
}
