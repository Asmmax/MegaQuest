#pragma once
#include "Containers/ContainerCollection.hpp"
#include "Containers/Container.hpp"
#include "Containers/Factory.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/IContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Register.hpp"

class IContainerReader;

class Context
{
	using ContainerReaderPtr = std::shared_ptr<IContainerReader>;
public:
	Context(const std::string& id):
		_id(id)
	{
		Register::Instance().RegisterContext(*this);
	}

	template <typename Type>
	std::shared_ptr<Container<Type>> GetContainer() {
		return ContainerCollection<Container, Type>::Instance().GetContainer(_id);
	}

	template <typename Type>
	std::shared_ptr<Factory<Type>> GetFactory()
	{
		return ContainerCollection<Factory, Type>::Instance().GetContainer(_id);
	}

	void RegisterContainerReader(const ContainerReaderPtr& container)
	{
		_containerReaders.push_back(container);
	}

	void AddRoot(const nlohmann::json& root)
	{
		for (auto& container : _containerReaders) {
			container->AddRoot(root);
		}
	}

	void Read()
	{
		for (auto& container : _containerReaders) {
			container->CreateAll();
		}

		for (auto& container : _containerReaders) {
			container->InitAll();
		}
	}


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

private:
	std::string _id;
	std::vector<ContainerReaderPtr> _containerReaders;
};

#define DECLARE_READER(Type) template<> std::shared_ptr<IReaderStrategy<Type>> Context::GetReader();

DECLARE_READER(bool)
DECLARE_READER(int)
DECLARE_READER(size_t)
DECLARE_READER(std::string)



template<>
inline std::shared_ptr<IReaderStrategy<bool>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<bool>>();
}

template<>
inline std::shared_ptr<IReaderStrategy<int>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<int>>();
}

template<>
inline std::shared_ptr<IReaderStrategy<size_t>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<size_t>>();
}

template<>
inline std::shared_ptr<IReaderStrategy<std::string>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<std::string>>();
}
