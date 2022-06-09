#include "Factories/DialogFactory.hpp"
#include "Game/SimpleDialog.hpp"
#include "Game/SwitchDialog.hpp"
#include "Factories/IRootFactory.hpp"

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
    auto dialog = std::make_shared<Game::SimpleDialog>(_output, paragraph, caseContainer);
    dialogs.push_back(dialog);


    _dialog = std::make_shared<Game::SwitchDialog>(dialogs);

    _isRed = true;
}

Game::IDialog::Ptr DialogFactory::GetDialog()
{
    Read();
    return _dialog;
}
