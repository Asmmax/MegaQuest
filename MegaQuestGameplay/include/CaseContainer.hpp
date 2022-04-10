#pragma once
#include "ActionContainer.hpp"
#include "IParagraph.hpp"

namespace QuestCore
{
	class CaseContainer : public ActionContainer, public IParagraph
	{
	public:
		virtual std::string GetCases() const override;
		virtual int GetCaseCount() const override;
		virtual void Answer(int caseID) override;
	};
}
