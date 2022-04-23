#pragma once
#include "IRoom.hpp"

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
	public:
		SimpleRoom(const TextString& name, const std::shared_ptr<IParagraph>& startParagraph);
		virtual const TextString& GetName() const override;
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const override;

	private:
		TextString _name;
		std::shared_ptr<IParagraph> _currentParagraph;
	};
}
