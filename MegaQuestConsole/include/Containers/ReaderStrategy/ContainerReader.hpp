#pragma once
#include "Containers/IReaderStrategy.hpp"
#include "Containers/Container.hpp"
#include "Containers/ContextManager.hpp"
#include <memory>
#include <assert.h>

template<typename Type>
class ContainerReader;

template<typename Type>
class ContainerReader<std::shared_ptr<Type>> : public IReaderStrategy<std::shared_ptr<Type>>
{
	using TypePtr = std::shared_ptr<Type>;
	using ContainerPtr = std::weak_ptr<Container<Type>>;

public:
	ContainerReader(const ContainerPtr& container) :
		_container(container)
	{
	}

	TypePtr Create(const nlohmann::json& node) override
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		auto result = ParseId(id);
		if (result.first.empty()) {
			return CreateBySimpleId(result.second);
		}
		return CreateByComplexId(result.first, result.second);
	}

	void Init(const nlohmann::json& node) override
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->InitById(id);
	}

private:
	TypePtr CreateByComplexId(const std::string& contextId, const std::string& id)
	{
		auto containerPtr = ContextManager::Instance().GetContext(contextId).GetContainer<Type>();
		assert(containerPtr);
		containerPtr->CreateById(id);
		return containerPtr->Get(id);
	}

	TypePtr CreateBySimpleId(const std::string& id)
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		containerPtr->CreateById(id);
		if (auto result = containerPtr->Get(id)) {
			return result;
		}

		auto globalContainerPtr = ContextManager::Instance().GetContext().GetContainer<Type>();
		if (globalContainerPtr == containerPtr) {
			return nullptr;
		}

		globalContainerPtr->CreateById(id);
		return globalContainerPtr->Get(id);
	}

	std::pair<std::string, std::string> ParseId(const std::string& complexId)
	{
		auto delimiterPos = complexId.find("/");
		if (delimiterPos == std::string::npos) {
			return std::pair<std::string, std::string>("", complexId);
		}
		return std::make_pair<std::string, std::string>(complexId.substr(0, delimiterPos), complexId.substr(delimiterPos + 1));
	}

private:
	ContainerPtr _container;
};
