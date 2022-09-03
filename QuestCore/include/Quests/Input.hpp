#pragma once
#include "Quests/IInput.hpp"
#include "Quests/QuestInitable.hpp"
#include "Quests/Slot.hpp"
#include <memory>

namespace QuestCore
{
	template <typename T>
	class Input : public IInput<T>, public QuestInitable, public std::enable_shared_from_this<Input<T>>
	{
		using SlotPtr = std::shared_ptr<Slot<T>>;
		using TPtr = std::shared_ptr<T>;
	public:
		Input(const TPtr& ptr,
			const SlotPtr& slot,
			const QuestPtr& quest):

			QuestInitable(quest),
			_ptr(ptr),
			_slot(slot)
		{
		}

		virtual void Init() override
		{
			_slot->SetInput(weak_from_this());
		}

		virtual TPtr Get() const override
		{
			return _ptr;
		}

	private:
		SlotPtr _slot;
		TPtr _ptr;
	};
}
