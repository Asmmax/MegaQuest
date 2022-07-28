#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainerInput;
	class ICaseContainer;

	/// @serializable
	class CaseContainerSlot : public ISlot
	{
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		virtual void Update() override;
		void SetInput(CaseContainerInput* input);
		CaseContainerPtr GetCaseContainer() const;

	private:
		CaseContainerInput* _input;
	};
}
