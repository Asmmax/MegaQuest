#pragma once
#include "Containers/IReaderStrategy.hpp"
#include <map>

template<typename EnumType>
class EnumReader : public IReaderStrategy<EnumType>
{
public:
	EnumReader(const std::map<std::string, EnumType>& values):
		_values(values)
	{
	}

	EnumType Create(const nlohmann::json& node) override
	{
		auto enumType = node.get<std::string>();
		return _values[enumType];
	}

	void Init(const nlohmann::json& /*node*/) override
	{
	}

private:
	std::map<std::string, EnumType> _values;
};
