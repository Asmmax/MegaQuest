#include "Game/DialogFactory.hpp"
#include "Game/Dialog.hpp"
#include "Game/IOutput.hpp"

using namespace Game;

DialogFactory::DialogFactory(const IOutput::Ptr& output) :
	_output(output)
{
}

QuestCore::ITextView& DialogFactory::GetTextView(const std::string& rootKey)
{
	return *GetDialog(rootKey);
}

QuestCore::IButtonPanel& DialogFactory::GetButtonPanel(const std::string& rootKey)
{
	return *GetDialog(rootKey);
}

const Dialog::Ptr& DialogFactory::GetDialog(const std::string& rootKey)
{
	auto foundIt = _dialogs.find(rootKey);
	if (foundIt == _dialogs.end()) {
		auto dialog = std::make_shared<Dialog>(_output);
		auto res = _dialogs.emplace(rootKey, dialog);
		foundIt = res.first;
	}
	return foundIt->second;
}
