#include "Factories/DialogFactory.hpp"
#include "Game/Dialog.hpp"
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

    _dialogs.clear();

    auto paragraph = _rootFactory->GetRootParagraph("root");
    auto caseContainer = _rootFactory->GetRootCaseContainer("root");
    auto dialog = std::make_shared<Game::Dialog>(_output, paragraph, caseContainer);
    _dialogs.push_back(dialog);

    _isRed = true;
}

std::vector<Game::Dialog::Ptr> DialogFactory::GetDialogs()
{
    Read();
    return _dialogs;
}
