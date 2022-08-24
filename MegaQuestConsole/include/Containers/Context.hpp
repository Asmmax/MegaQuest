#pragma once
#include "Containers/ContainerCollection.hpp"
#include "Containers/Container.hpp"
#include "Containers/Factory.hpp"

class IContainerReader;

class Context
{
	using ContainerReaderPtr = std::shared_ptr<IContainerReader>;
public:
	Context(const std::string& id);

	static Context& Global();

	template <typename Type>
	std::shared_ptr<Container<Type>> GetContainer() {
		return ContainerCollection<Container, Type>::Instance().GetContainer(_id);
	}

	template <typename Type>
	std::shared_ptr<Factory<Type>> GetFactory()
	{
		return ContainerCollection<Factory, Type>::Instance().GetContainer(_id);
	}

	void RegisterContainerReader(const ContainerReaderPtr& container);

	void AddRoot(const nlohmann::json& root);
	void Read();

private:
	std::string _id;
	std::vector<ContainerReaderPtr> _containerReaders;
};
