#pragma once
#include "json.hpp"
#include <memory>
#include <string>

template<typename BaseType>
class IFactoryImpl
{
public:
	virtual ~IFactoryImpl() = default;

	virtual void InitDependencies(const nlohmann::json& node) = 0;
	virtual bool IsSuitType(const std::string& typeName) = 0;
	virtual BaseType GetBase(const nlohmann::json& node) = 0;
};
