#include "QuestBase.hpp"
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"

using namespace QuestCore;

QuestBase::QuestBase(const TextViewFactoryPtr& viewFactory, const ButtonsFactoryPtr& buttonsFactory):
	_viewFactory(viewFactory),
	_buttonsFactory(buttonsFactory)
{
}

void QuestBase::Update()
{
	auto& roots = GetRoots();
	for (auto& root : roots) {
		auto& view = _viewFactory->GetTextView(root.first);
		view.Clear();
		root.second.paragraph->Print(view);

		auto& buttons = _buttonsFactory->GetButtonPanel(root.first);
		buttons.RemoveAllButtons();
		root.second.caseContainer->Print(buttons);
	}
}