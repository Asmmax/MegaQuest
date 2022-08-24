#include "Containers/Context.hpp"
#include "Containers/IContainerReader.hpp"

Context::Context(const std::string& id) :
	_id(id)
{
}

Context& Context::Global() {
	static Context globalContext("");
	return globalContext;
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
