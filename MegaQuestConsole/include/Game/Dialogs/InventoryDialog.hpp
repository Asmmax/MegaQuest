#pragma once
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class Inventory;
}

namespace Game
{
	class IOutput;

	/// @serializable
	class InventoryDialog : public DialogBase
	{
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		InventoryDialog(const OutputPtr& output, const QuestCore::TextString& intro, const InventoryPtr& inventory);
		virtual void Draw() override;
		
	private:
		InventoryPtr _inventory;
	};
}
