#pragma once
#include "IFactoryImpl.hpp"
#include "Utils/Reader.hpp"
#include <vector>

template<typename Type>
class Factory
{
	using FactoryImplPtr = std::shared_ptr<IFactoryImpl<Type>>;
public:

	void AddInheritor(const FactoryImplPtr& inheritor)
	{
		_inheritors.push_back(inheritor);
	}

	Type Get(const nlohmann::json& node)
	{
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		for (auto& inheritor : _inheritors) {
			if (inheritor->IsSuitType(typeId)) {
				return inheritor->GetBase(node);
			}
		}
		return Type();
	}

	void InitDependencies(const nlohmann::json& node)
	{
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		for (auto& inheritor : _inheritors) {
			if (inheritor->IsSuitType(typeId)) {
				return inheritor->InitDependencies(node);
			}
		}
	}

private:
	std::vector<FactoryImplPtr> _inheritors;
};
