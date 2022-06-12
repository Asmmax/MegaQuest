#pragma once
#include "Game/Dialogs/IntroDialog.hpp"
#include <vector>

namespace QuestCore
{
	class Inventory;
}

namespace Game
{
	class IOutput;

	class InventoryDialog : public IntroDialog
	{
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;
		using OutputPtr = std::shared_ptr<IOutput>;
		using ButtonListPtr = std::shared_ptr<IButtonList>;

	public:
		InventoryDialog(const OutputPtr& output, const QuestCore::TextString& intro, const InventoryPtr& inventory);

		void AddButtonList(const ButtonListPtr& buttonList);
		virtual void Update() override;
		
	private:
		InventoryPtr _inventory;
		std::vector<ButtonListPtr> _buttonGroups;
	};
}