#include "Containers/GlobalRootReader.hpp"

GlobalRootReader& GlobalRootReader::Instance() 
{
	static GlobalRootReader instance;
	return instance;
}

void GlobalRootReader::AddRoot(const nlohmann::json& root)
{
	for (auto& addRootCallback : _addRootCallbacks)
	{
		addRootCallback(root);
	}
}

void GlobalRootReader::Read()
{
	for (auto& createAllCallback : _createAllCallbacks)
	{
		createAllCallback();
	}

	for (auto& initAllCallback : _initAllCallbacks)
	{
		initAllCallback();
	}
}
