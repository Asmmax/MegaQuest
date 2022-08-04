#pragma once
#include <memory>
#include <string>

template<typename BaseType>
class IContainerImpl
{
	using BaseTypePtr = std::shared_ptr<BaseType>;
public:
	virtual ~IContainerImpl() = default;

	virtual void CreateById(const std::string& id) = 0;
	virtual void InitById(const std::string& id) = 0;

	virtual BaseTypePtr GetBase(const std::string& id) = 0;
	virtual BaseTypePtr GetBase() = 0;

	virtual bool Contains(const std::string& id) = 0;
	virtual bool Empty() = 0;
};
