#pragma once
#include "Containers/IFactoryImpl.hpp"

template<typename ImplType, typename BaseType>
class FactoryImplBase : public IFactoryImpl<BaseType>
{
public:
	BaseType GetBase(const nlohmann::json& node) override
	{
		return Get(node);
	}

	virtual ImplType Get(const nlohmann::json& node) = 0;
};

template<typename ImplType, typename... Bases>
class FactoryImplBases : public FactoryImplBase<ImplType, ImplType>, public FactoryImplBase<ImplType, Bases>... {};
