#pragma once
#include "json.hpp"
#include <map>

template<typename EnumType>
class EnumReader
{
public:
	EnumReader(const std::map<std::string, EnumType>& values):
		_values(values)
	{
	}

	EnumType Create(const nlohmann::json& node)
	{
		auto enumType = node.get<std::string>();
		return _values[enumType];
	}

	void Init(const nlohmann::json& /*node*/)
	{
	}

private:
	std::map<std::string, EnumType> _values;
};
