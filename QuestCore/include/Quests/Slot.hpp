#pragma once
#include "Quests/IInput.hpp"
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	template <typename T>
	class Slot : public QuestInitable
	{
	public:
		Slot(Quest* quest):
			QuestInitable(quest),
			_input(nullptr)
		{
		}

		virtual void Init() override
		{
			_input = nullptr;
		}

		void SetInput(IInput<T>* input)
		{
			_input = input;
		}

		T* Get() const
		{
			if (!_input) {
				return nullptr;
			}
			return _input->Get();
		}

	protected:
		IInput<T>* _input;
	};
}
