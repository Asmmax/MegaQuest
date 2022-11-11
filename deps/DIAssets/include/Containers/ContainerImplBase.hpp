#pragma once
#include "Containers/IContainerImpl.hpp"

template<typename ImplType, typename BaseType>
class ContainerImplBase : public IContainerImpl<BaseType>
{
	using ImplTypePtr = std::shared_ptr<ImplType>;
	using BaseTypePtr = std::shared_ptr<BaseType>;
	static_assert(std::is_base_of<BaseType, ImplType>::value);
public:
	BaseTypePtr GetBase(const std::string& id) override
	{
		return Get(id);
	}

	BaseTypePtr GetBase() override
	{
		return Get();
	}

	virtual ImplTypePtr Get(const std::string& id) = 0;
	virtual ImplTypePtr Get() = 0;
};

template<typename ImplType, typename... Bases>
class ContainerImplBases : public ContainerImplBase<ImplType, ImplType>, public ContainerImplBase<ImplType, Bases>... {};
