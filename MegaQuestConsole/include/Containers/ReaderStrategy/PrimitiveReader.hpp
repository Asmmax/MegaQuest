#pragma once
#include "json.hpp"

template<typename Type>
class PrimitiveReader
{
public:
	Type Create(const nlohmann::json& node)
	{
		return node.get<Type>();
	}

	void Init(const nlohmann::json& /*node*/)
	{
	}
};
