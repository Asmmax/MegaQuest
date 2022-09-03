#pragma once
#include "Quests/IInput.hpp"
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	template <typename T>
	class Slot : public QuestInitable
	{
		using TPtr = std::shared_ptr<T>;
		using InputWeakPtr = std::weak_ptr<IInput<T>>;
	public:
		Slot(const QuestPtr& quest):
			QuestInitable(quest)
		{
		}

		virtual void Init() override
		{
			_input = InputWeakPtr();
		}

		void SetInput(const InputWeakPtr& input)
		{
			_input = input;
		}

		TPtr Get() const
		{
			if (_input.expired()) {
				return nullptr;
			}
			auto inputPtr = _input.lock();
			return inputPtr->Get();
		}

	protected:
		InputWeakPtr _input;
	};
}
