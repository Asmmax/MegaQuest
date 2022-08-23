#pragma once
#include "Containers/ContainerCollection.hpp"
#include "Containers/IContainer.hpp"
#include "Containers/IFactory.hpp"

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
	std::shared_ptr<IContainer<Type>> GetContainer() {
		return ContainerCollection<IContainer, Type>::Instance().GetContainer(_id);
	}

	template <typename Type>
	std::shared_ptr<IFactory<Type>> GetFactory()
	{
		return ContainerCollection<IFactory, Type>::Instance().GetContainer(_id);
	}
private:
	std::string _id;
};
