#pragma once
#include "ICaseContainer.hpp"
#include <map>

namespace QuestCore
{
	class SimpleCaseContainer: public ICaseContainer
	{
	public:
		virtual void Print(IButtonPanel& buttonPanel) override;

		void Clear();
		void AddCase(const Case& _case);
		void AddCase(const std::string& key, const Case& _case);

	private:
		mutable std::map<std::string, std::vector<Case>> _cases;
	};
}
