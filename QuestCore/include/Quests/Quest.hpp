#pragma once
#include "IQuest.hpp"
#include <vector>
#include <functional>

namespace QuestCore
{
	class Quest : public IQuest
	{
	protected:
		using Callback = std::function<void()>;

	public:
		void AddInitCallback(const Callback& callback);
		virtual void Init() override;

	private:
		std::vector<Callback> _initCallbacks;
	};
}
