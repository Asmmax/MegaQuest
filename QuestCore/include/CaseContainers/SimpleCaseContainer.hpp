#pragma once
#include "ICaseContainer.hpp"
#include <vector>

namespace QuestCore
{
	class SimpleCaseContainer: public ICaseContainer
	{
	public:
		virtual void Print(IButtonGroup& buttons) override;

		void Clear();
		void AddCase(const Case& _case);

	private:
		mutable std::vector<Case> _cases;
	};
}
