#pragma once
#include "GlobalContext.hpp"
#include <functional>
#include <vector>

class IContainerReader;

class GlobalRootReader
{
	using ContainerReaderPtr = std::shared_ptr<IContainerReader>;
public:
	static GlobalRootReader& Instance();

	void AddContainer(const ContainerReaderPtr& container);

	void AddRoot(const nlohmann::json& root);
	void Read();

private:
	std::vector<ContainerReaderPtr> _containers;
};
