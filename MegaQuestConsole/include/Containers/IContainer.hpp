#pragma once
#include <string>
#include <memory>

template<typename Type>
class IContainer
{
	using TypePtr = std::shared_ptr<Type>;

public:
	virtual ~IContainer() = default;

	virtual void CreateById(const std::string& id) = 0;
	virtual void InitById(const std::string& id) = 0;

	virtual TypePtr Get(const std::string& id) = 0;
	virtual TypePtr Get() = 0;
};
