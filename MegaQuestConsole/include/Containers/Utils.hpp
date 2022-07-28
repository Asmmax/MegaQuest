#pragma once
#include "Containers/PropertyReader.hpp"
#include "Containers/MethodInitializer.hpp"
#include <type_traits>

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


template<>
std::shared_ptr<IReaderStrategy<bool>> GetReader();

template<>
std::shared_ptr<IReaderStrategy<int>> GetReader();

template<>
std::shared_ptr<IReaderStrategy<size_t>> GetReader();

template<>
std::shared_ptr<IReaderStrategy<std::string>> GetReader();
