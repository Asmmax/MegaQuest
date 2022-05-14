#include "Factories/DialogFactory.hpp"
#include "Game/Dialog.hpp"

DialogFactory::DialogFactory(const OutputPtr& output):
    _isRed(false),
    _output(output)
{
}

void DialogFactory::Read()
{
    if (_isRed) {
        return;
    }

    _dialogs.clear();

    auto dialog = std::make_shared<Game::Dialog>(_output);
    _dialogs.emplace("root", dialog);

    _isRed = true;
}

std::shared_ptr<QuestCore::ITextView> DialogFactory::GetTextView(const std::string& root)
{
	return GetDialog(root);
}

std::shared_ptr<QuestCore::IButtonPanel> DialogFactory::GetButtonPanel(const std::string& root)
{
	return GetDialog(root);
}

std::vector<Game::Dialog::Ptr> DialogFactory::GetDialogs()
{
    Read();

    std::vector<Game::Dialog::Ptr> dialogs;

    for (auto& dialog : _dialogs) {
        dialogs.push_back(dialog.second);
    }
    return dialogs;
}

Game::Dialog::Ptr DialogFactory::GetDialog(const std::string& root)
{
    Read();

    auto foundIt = _dialogs.find(root);
    if (foundIt == _dialogs.end()) {
        return nullptr;
    }
    return foundIt->second;
}
