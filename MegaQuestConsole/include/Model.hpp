#pragma once
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include "IModel.hpp"
#include <map>

class IInput;
class IOutput;

namespace QuestCore
{
	class QuestBase;
	class IQuestFactory;
}

class ButtonList : public QuestCore::IButtonGroup
{
	struct Button
	{
		QuestCore::TextString name;
		std::function<void()> callback;
	};

public:
	using Ptr = std::shared_ptr<ButtonList>;

	ButtonList(const std::function<void()>& finishCallback);
	virtual void AddButton(const QuestCore::TextString& text, const std::function<void()>& callback) override;
	void Do();
	void Do(int answer);
	std::vector<QuestCore::TextString> GetNames() const;
	size_t GetButtonCount() const;

private:
	std::function<void()> _finishCallback;
	std::vector<Button> _buttons;
};




class Dialog : public QuestCore::ITextView, public QuestCore::IButtonPanel
{
	using OutputPtr = std::shared_ptr<IOutput>;
	using QuestPtr = std::shared_ptr<QuestCore::QuestBase>;
	using ButtonListPtr = std::shared_ptr<ButtonList>;

public:
	using Ptr = std::shared_ptr<Dialog>;

	Dialog(const OutputPtr& output);
	virtual void Clear() override;
	virtual void RemoveAllButtons() override;
	virtual void AppendText(const QuestCore::TextString& text) override;
	virtual QuestCore::IButtonGroup& GetButtonGroup(const std::string& actionKey) override;
	ButtonListPtr GetDefaultButtonList();
	ButtonListPtr GetInventoryButtonList();
	void SetQuest(const QuestPtr& quest);
	void Update();
	bool Answer(int answer);
	void OpenInventory();

private:
	OutputPtr _output;
	QuestPtr _quest;
	QuestCore::TextString _text;
	std::map<std::string, ButtonListPtr> _buttonGroups;
};



class DialogFactory : public QuestCore::ITextViewFactory, public QuestCore::IButtonPanelFactory
{
	using OutputPtr = std::shared_ptr<IOutput>;
	using DialogPtr = std::shared_ptr<Dialog>;

public:
	DialogFactory(const OutputPtr& output);
	virtual QuestCore::ITextView& GetTextView(const std::string& rootKey) override;
	virtual QuestCore::IButtonPanel& GetButtonPanel(const std::string& rootKey) override;
	const DialogPtr& GetDialog(const std::string& rootKey);

private:
	OutputPtr _output;
	std::map<std::string, DialogPtr> _dialogs;
};




class Model : public IModel
{
	using OutputPtr = std::shared_ptr<IOutput>;
	using QuestFactoryPtr = std::shared_ptr<QuestCore::IQuestFactory>;
	using DialogFactoryPtr = std::shared_ptr<DialogFactory>;
	using DialogPtr = std::shared_ptr<Dialog>;
	using QuestPtr = std::shared_ptr<QuestCore::QuestBase>;

public:
	Model(const OutputPtr& output, const QuestFactoryPtr& questFactory);
	virtual void OpenInventory() override;
	virtual bool Handle(int answer) override;
	virtual void Init() override;

private:
	OutputPtr _output;
	QuestFactoryPtr _questFactory;
	DialogFactoryPtr _dialogFactory;
	DialogPtr _currentDialog;
	QuestPtr _quest;
};
