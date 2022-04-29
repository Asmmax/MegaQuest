#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>
#include <map>

namespace QuestCore
{
	class IAction;

	struct Case
	{
		TextString name;
		std::shared_ptr<IAction> action;
	};

	class CaseContainer
	{
	public:
		virtual ~CaseContainer() = default;

		void Clear();
		size_t GetCaseCount() const;
		void AddCase(const Case& _case);
		void AddCase(const std::string& key, const Case& _case);
		const std::vector<Case>& GetCases(const std::string& key = std::string()) const;

		CaseContainer& operator+=(const CaseContainer& other);

	private:
		mutable std::map<std::string, std::vector<Case>> _cases;
	};
}
