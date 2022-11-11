#pragma once
#include "Containers/IReaderStrategy.hpp"

template<typename Type>
class PrimitiveReader : public IReaderStrategy<Type>
{
public:
	Type Create(const nlohmann::json& node) override
	{
		return node.get<Type>();
	}

	void Init(const nlohmann::json& /*node*/) override
	{
	}
};
