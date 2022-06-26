#pragma once
#include "json.hpp"
#include <memory>

template<typename Type>
class IFactory
{
public:

	virtual ~IFactory() = default;
	virtual Type Get(const nlohmann::json& node) = 0;
	virtual void InitDependencies(const nlohmann::json& node) = 0;
};
