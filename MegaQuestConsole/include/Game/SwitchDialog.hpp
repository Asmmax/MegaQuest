#pragma once
#include "Game/IDialog.hpp"
#include <memory>
#include <vector>
#include <string>

namespace Game
{
	class SwitchDialog : public IDialog
	{
		using DialogPtr = std::shared_ptr<IDialog>;
		using ButtonListPtr = std::shared_ptr<ButtonList>;

	public:
		using Ptr = std::shared_ptr<SwitchDialog>;

		SwitchDialog(const std::vector<DialogPtr>& dialogs);
		virtual ButtonListPtr GetButtonList(const std::string& key = std::string()) override;
		virtual void Update() override;

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
	};
}
