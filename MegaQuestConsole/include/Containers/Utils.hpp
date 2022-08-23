#pragma once
#include "Containers/PropertyReader.hpp"
#include "Containers/MethodInitializer.hpp"

template <typename Type>
std::shared_ptr<IReaderStrategy<Type>> GetReader();

template<typename ArgType>
PropertyReader<ArgType> CreateProperty(const std::string& name, const ArgType& defValue)
{
	return PropertyReader<ArgType>(name, GetReader<ArgType>(), defValue);
}

template<typename ArgType>
PropertyReader<ArgType> CreateProperty(const std::string& name, const std::vector<typename ArgType::value_type>& defValue)
{
	return PropertyReader<ArgType>(name, GetReader<typename ArgType::value_type>(), defValue);
}

template<typename ElementType, typename ArgType>
MethodInitializer<ElementType, ArgType> CreateMethod(
	const std::string& name,
	const ArgType& defValue,
	const std::function<void(const std::shared_ptr<ElementType>&, const ArgType&)>& callback)
{
	return MethodInitializer<ElementType, ArgType>(CreateProperty<ArgType>(name, defValue), callback);
}

#define DECLARE_READER(Type) template<> std::shared_ptr<IReaderStrategy<Type>> GetReader();

DECLARE_READER(bool)
DECLARE_READER(int)
DECLARE_READER(size_t)
DECLARE_READER(std::string)
