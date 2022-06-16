#pragma once
#include "FormatedString.hpp"
#include <memory>

namespace QuestCore
{
	/// @serializable @shared
	class Item
	{
	public:
		using Ptr = std::shared_ptr<Item>;

		Item(const std::string& name, const FormatedString& text, bool isNullable = false);
		TextString GetContains(int count) const;
		inline bool IsNullable() const { return _isNullable; }
		inline const std::string& GetName() const { return _name; }

	private:
		FormatedString _text;
		bool _isNullable;
		std::string _name;
	};
}
