#pragma once
#include <memory>
#include <vector>

namespace Game
{
	class ButtonList;
	class Dialog;

	class Model
	{
		using DialogPtr = std::shared_ptr<Dialog>;

	public:
		using Ptr = std::shared_ptr<Model>;

		Model(const std::vector<DialogPtr>& dialogs);
		void OpenInventory();
		void Handle(int answer);
		void Update();

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
	};
}
