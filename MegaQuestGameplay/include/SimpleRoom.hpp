#pragma once
#include "IRoom.hpp"

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
	public:
		SimpleRoom(const TextString& name, const std::shared_ptr<IParagraph>& startParagraph, const std::vector<std::string>& hotKeys);
		virtual const TextString& GetName() const override;
		virtual const std::shared_ptr<IParagraph>& GetCurrentParagraph() const override;
		virtual std::vector<std::string> GetHotKeys() const override;

	private:
		TextString _name;
		std::vector<std::string> _hotKeys;
		std::shared_ptr<IParagraph> _currentParagraph;
	};
}
