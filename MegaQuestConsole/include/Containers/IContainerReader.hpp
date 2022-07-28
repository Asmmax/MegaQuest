#pragma once
#include "json.hpp"

class IContainerReader
{
public:
	virtual ~IContainerReader() = default;
	virtual void AddRoot(const nlohmann::json& root) = 0;
	virtual void CreateAll() = 0;
	virtual void InitAll() = 0;
};
