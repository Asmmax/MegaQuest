#pragma once
#include "json.hpp"

template<typename Type>
class IReaderStrategy
{
public:
	virtual ~IReaderStrategy() = default;

	virtual Type Create(const nlohmann::json& node) = 0;
	virtual void Init(const nlohmann::json& node) = 0;
};
