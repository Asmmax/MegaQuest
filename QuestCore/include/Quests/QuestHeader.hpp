#pragma once
#include "IQuest.hpp"
#include <vector>

namespace QuestCore
{
	class ISlot;

	/// @serializable
	class QuestHeader : public IQuest
	{
	protected:
		using SlotPtr = std::shared_ptr<ISlot>;

	public:
		QuestHeader(const std::vector<SlotPtr>& slots);
		virtual void Init() override;
		void UpdateSlots();
		void Reset();

	private:
		std::vector<SlotPtr> _slots;
	};
}
