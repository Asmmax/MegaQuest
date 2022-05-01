#pragma once
#include "FormatedString.hpp"

namespace QuestCore
{
	class Item
	{
	public:
		Item(const std::string& id, const FormatedString& text, bool isNullable = false);
		TextString GetContains(int count) const;
		inline bool IsNullable() const { return _isNullable; }
		bool operator<(const Item& other) const;

	private:
		std::string _id;
		FormatedString _text;
		bool _isNullable;
	};

	struct ItemComparator {
		bool operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const {
			return *left < *right;
		}
	};
}