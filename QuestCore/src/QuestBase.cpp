#include "QuestBase.hpp"
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"

using namespace QuestCore;

void Root::Update()
{
	textView->Clear();
	paragraph->Print(*textView);

	buttons->RemoveAllButtons();
	caseContainer->Print(*buttons);
}

QuestBase::QuestBase(const std::vector<Root>& roots):
	_roots(roots)
{
}

void QuestBase::Update()
{
	for (auto root : _roots) {
		root.Update();
	}
}
