#pragma once
#include "Quests/IInput.hpp"
#include "Quests/QuestInitable.hpp"
#include "Quests/Slot.hpp"
#include <memory>

namespace QuestCore
{
	template <typename T>
	class Input : public IInput<T>, public QuestInitable
	{
	public:
		Input(T* ptr,
			Slot<T>* slot,
			Quest* quest):

			QuestInitable(quest),
			_ptr(ptr),
			_slot(slot)
		{
		}

		virtual void Init() override
		{
			_slot->SetInput(this);
		}

		virtual T* Get() const override
		{
			return _ptr;
		}

	private:
		Slot<T>* _slot;
		T* _ptr;
	};
}
