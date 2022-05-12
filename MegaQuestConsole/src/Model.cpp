#include "Model.hpp"
#include "IInput.hpp"
#include "IOutput.hpp"
#include "QuestBase.hpp"
#include "IQuestFactory.hpp"

ButtonList::ButtonList(const std::function<void()>& finishCallback) :
	_finishCallback(finishCallback)
{
}

void ButtonList::AddButton(const QuestCore::TextString& text, const std::function<void()>& callback)
{
	Button button{ text, [this, callback]() {
		callback();
		_finishCallback();
	} };
	_buttons.push_back(button);
}

void ButtonList::Do()
{
	_buttons[0].callback();
}

void ButtonList::Do(int answer)
{
	_buttons[answer].callback();
}

std::vector<QuestCore::TextString> ButtonList::GetNames() const
{
	std::vector<QuestCore::TextString> _names;
	for (auto& button : _buttons) {
		_names.push_back(button.name);
	}
	return _names;
}

size_t ButtonList::GetButtonCount() const
{
	return _buttons.size();
}







Dialog::Dialog(const IOutput::Ptr& output):
	_output(output)
{
}

void Dialog::Clear()
{
	_text = QuestCore::TextString();
}

void Dialog::RemoveAllButtons()
{
	_buttonGroups.clear();
}

void Dialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

QuestCore::IButtonGroup& Dialog::GetButtonGroup(const std::string& actionKey)
{
	auto foundIt = _buttonGroups.find(actionKey);
	if (foundIt == _buttonGroups.end()) {
		auto buttonGroup = std::make_shared<ButtonList>([this]() {
			if (_quest) {
				_quest->Update();
			}
			});
		auto res = _buttonGroups.emplace(actionKey, buttonGroup);
		foundIt = res.first;
	}
	return *foundIt->second;
}

ButtonList::Ptr Dialog::GetDefaultButtonList()
{
	auto foundIt = _buttonGroups.find("");
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

ButtonList::Ptr Dialog::GetInventoryButtonList()
{
	auto foundIt = _buttonGroups.find("inventory");
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

void Dialog::SetQuest(const QuestCore::QuestBase::Ptr& quest)
{
	_quest = quest;
}

void Dialog::Update()
{
	_output->WriteLn(_text);
	auto defaultButtons = GetDefaultButtonList();
	if (!defaultButtons) {
		return;
	}

	auto names = defaultButtons->GetNames();
	int num = 1;
	for (auto& name : names) {
		_output->WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}

bool Dialog::Answer(int answer)
{
	if (answer < 0) {
		return false;
	}

	auto defaultButtons = GetDefaultButtonList();
	if (!defaultButtons) {
		return false;
	}

	auto buttonCount = defaultButtons->GetButtonCount();
	if (answer >= buttonCount) {
		return false;
	}

	defaultButtons->Do(answer);
	return true;
}

void Dialog::OpenInventory()
{
	auto inventoryButtons = GetInventoryButtonList();
	if (!inventoryButtons) {
		return;
	}

	inventoryButtons->Do();
}








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



Model::Model(const OutputPtr& output, const QuestFactoryPtr& questFactory):
	_output(output),
	_questFactory(questFactory)
{
	_dialogFactory = std::make_shared<DialogFactory>(output);
	_quest = _questFactory->GetQuest(_dialogFactory, _dialogFactory);
	_currentDialog = _dialogFactory->GetDialog("root");
	_currentDialog->SetQuest(_quest);
}

void Model::OpenInventory()
{
	_currentDialog->OpenInventory();
	_currentDialog->Update();
}

bool Model::Handle(int answer)
{
	if (_currentDialog->Answer(answer)) {
		_currentDialog->Update();
		return true;
	}

	return false;
}

void Model::Init()
{
	_quest->Update();
	_currentDialog->Update();
}
