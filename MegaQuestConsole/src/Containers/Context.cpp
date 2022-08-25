#include "Containers/Context.hpp"
#include "Containers/IContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Register.hpp"

Context::Context(const std::string& id) :
	_id(id)
{
	Register::Instance().RegisterContext(*this);
}

void Context::RegisterContainerReader(const ContainerReaderPtr& container)
{
	_containerReaders.push_back(container);
}

void Context::AddRoot(const nlohmann::json& root)
{
	for (auto& container : _containerReaders) {
		container->AddRoot(root);
	}
}

void Context::Read()
{
	for (auto& container : _containerReaders) {
		container->CreateAll();
	}

	for (auto& container : _containerReaders) {
		container->InitAll();
	}
}



template<>
std::shared_ptr<IReaderStrategy<bool>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<bool>>();
}

template<>
std::shared_ptr<IReaderStrategy<int>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<int>>();
}

template<>
std::shared_ptr<IReaderStrategy<size_t>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<size_t>>();
}

template<>
std::shared_ptr<IReaderStrategy<std::string>> Context::GetReader()
{
	return std::make_shared<PrimitiveReader<std::string>>();
}
