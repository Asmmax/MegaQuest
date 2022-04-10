#pragma once
#include "IRoom.hpp"

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
	public:
		SimpleRoom(const std::string& name, const std::shared_ptr<IParagraph>& startParagraph);
		virtual const std::string& GetName() const override;
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const override;

	private:
		std::string _name;
		std::shared_ptr<IParagraph> _currentParagraph;
	};
}
