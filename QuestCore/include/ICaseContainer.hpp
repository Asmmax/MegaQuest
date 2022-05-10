#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class IAction;

	struct Case
	{
	private:
		using ActionPtr = std::shared_ptr<IAction>;

	public:
		TextString name;
		ActionPtr action;
	};

	class ICaseContainer
	{
	public:
		using Ptr = std::shared_ptr<ICaseContainer>;

		virtual ~ICaseContainer() = default;

		virtual const std::vector<Case>& GetCases(const std::string& key = std::string()) const = 0;
		virtual size_t GetCaseCount() const = 0;
	};
}
