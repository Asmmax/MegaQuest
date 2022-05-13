#pragma once
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include <map>

namespace Game
{
	class IOutput;
	class Dialog;

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
}
