#pragma once
#include "IRoom.hpp"
#include <map>

namespace QuestCore
{
	class SimpleRoom : public IRoom
	{
		using InputList = std::map<std::string, std::shared_ptr<IParagraph>>;
	public:
		SimpleRoom(const InputList& inputs, const std::vector<std::string>& hotKeys);
		virtual const std::shared_ptr<IParagraph>& GetParagraph(const std::string& key) const override;
		virtual std::vector<std::string> GetHotKeys() const override;

	private:
		std::vector<std::string> _hotKeys;
		mutable InputList _paragraphs;
	};
}
