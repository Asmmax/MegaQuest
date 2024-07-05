#pragma once
#include "ICaseContainer.hpp"
#include <vector>

namespace QuestCore
{
	class SimpleCaseContainer: public ICaseContainer
	{
	public:
		SimpleCaseContainer(const std::vector<Case>& cases = std::vector<Case>());
		virtual void Print(IButtonGroup& buttons) override;

		void Clear();
		void AddCase(const Case& _case);

	private:
		mutable std::vector<Case> _cases;
	};
}
