#pragma once
#include "Factories/ITextViewFactory.hpp"
#include "Factories/IButtonPanelFactory.hpp"
#include <vector>
#include <map>

namespace Game 
{
	class Dialog;
	class IOutput;
}

class DialogFactory : public ITextViewFactory, public IButtonPanelFactory
{
	using OutputPtr = std::shared_ptr<Game::IOutput>;
	using DialogPtr = std::shared_ptr<Game::Dialog>;

public:
	DialogFactory(const OutputPtr& output);
	void Read();
	virtual TextViewPtr GetTextView(const std::string& root) override;
	virtual ButtonsPtr GetButtonPanel(const std::string& root) override;

	std::vector<DialogPtr> GetDialogs();

private:
	DialogPtr GetDialog(const std::string& root);

private:
	bool _isRed;
	OutputPtr _output;
	std::map<std::string, DialogPtr> _dialogs;
};
