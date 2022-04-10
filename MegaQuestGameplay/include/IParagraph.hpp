#pragma once
#include <string>

namespace QuestCore
{
	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual std::string GetQuest() const = 0;
		virtual std::string GetCases() const = 0;
		virtual int GetCaseCount() const = 0;
		virtual void Answer(int caseID) = 0;
	};
}
