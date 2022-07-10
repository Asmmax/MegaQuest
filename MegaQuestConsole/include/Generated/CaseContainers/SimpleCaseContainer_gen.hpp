#pragma once
#include "CaseContainers/SimpleCaseContainer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using SimpleCaseContainerInitializer = ContainerInitializer<QuestCore::SimpleCaseContainer>;

using SimpleCaseContainerImpl = ContainerImpl<QuestCore::SimpleCaseContainer,
    SimpleCaseContainerInitializer,
    std::vector<QuestCore::Case>
>;

class SimpleCaseContainerImpl_Binder
{
public:
    SimpleCaseContainerImpl_Binder();

private:
    static SimpleCaseContainerImpl_Binder instance;
};

using SimpleCaseContainerContainer = Container<QuestCore::SimpleCaseContainer, SimpleCaseContainerImpl>;

template<>
template<>
void ContainerBinder<QuestCore::SimpleCaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleCaseContainerImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::SimpleCaseContainer>>& GlobalContext::GetContainer<QuestCore::SimpleCaseContainer>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SimpleCaseContainer>>> GetReader();
