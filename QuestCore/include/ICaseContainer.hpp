#pragma once
#include "Case.hpp"
#include <string>
#include <memory>
#include <vector>

namespace QuestCore
{
	class ICaseContainer
	{
	public:
		using Ptr = std::shared_ptr<ICaseContainer>;

		virtual ~ICaseContainer() = default;

		virtual const std::vector<Case>& GetCases(const std::string& key = std::string()) const = 0;
		virtual size_t GetCaseCount() const = 0;
	};
}
