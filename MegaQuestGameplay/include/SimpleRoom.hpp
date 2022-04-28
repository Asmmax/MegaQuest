#pragma once
#include "IRoom.hpp"

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
	public:
		SimpleRoom(const std::shared_ptr<IParagraph>& startParagraph, const std::vector<std::string>& hotKeys);
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const override;
		virtual std::vector<std::string> GetHotKeys() const override;

	private:
		std::vector<std::string> _hotKeys;
		std::shared_ptr<IParagraph> _currentParagraph;
	};
}
