#pragma once
#include "json.hpp"
#include "TextString.hpp"

namespace Utils {

	template<typename T>
	inline T Read(const nlohmann::json& node, const std::string& key, const T& defValue)
	{
		auto foundIt = node.find(key);
		if (foundIt == node.end()) {
			return defValue;
		}

		return *foundIt;
	}

	template<>
	inline QuestCore::TextString Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue)
	{
		std::string rawDefValue = defValue.ToUtf8();
		return QuestCore::TextString::FromUtf8(Read(node, key, rawDefValue));
	}
}
