#pragma once
#include "Containers/ContainerCollection.hpp"
#include "Containers/Container.hpp"
#include "Containers/Factory.hpp"

class Context
{
public:
	Context(const std::string& id):
		_id(id)
	{
	}

	static Context& Global() {
		static Context globalContext("");
		return globalContext;
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

private:
	std::string _id;
};
