#include "Containers/GlobalRootReader.hpp"
#include "Containers/IContainerReader.hpp"

GlobalRootReader& GlobalRootReader::Instance() 
{
	static GlobalRootReader instance;
	return instance;
}

void GlobalRootReader::AddContainer(const ContainerReaderPtr& container)
{
	_containers.push_back(container);
}

void GlobalRootReader::AddRoot(const nlohmann::json& root)
{
	for (auto& container : _containers) {
		container->AddRoot(root);
	}
}

void GlobalRootReader::Read()
{
	for (auto& container : _containers) {
		container->CreateAll();
	}

	for (auto& container : _containers) {
		container->InitAll();
	}
}
