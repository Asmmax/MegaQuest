#pragma once
#include "CaseContainers/ConditionalCaseContainer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ConditionalCaseContainerInitializer = ContainerInitializer<QuestCore::ConditionalCaseContainer>;

using ConditionalCaseContainerImpl = ContainerImpl<QuestCore::ConditionalCaseContainer,
    ConditionalCaseContainerInitializer,
    std::shared_ptr<QuestCore::ICaseContainer>,
    std::shared_ptr<QuestCore::ICaseContainer>,
    std::vector<std::shared_ptr<QuestCore::ICondition>>
>;

class ConditionalCaseContainerImpl_Binder
{
public:
    ConditionalCaseContainerImpl_Binder();

private:
    static ConditionalCaseContainerImpl_Binder instance;
};

using ConditionalCaseContainerContainer = Container<QuestCore::ConditionalCaseContainer, ConditionalCaseContainerImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ConditionalCaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalCaseContainerImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ConditionalCaseContainer>>& GlobalContext::GetContainer<QuestCore::ConditionalCaseContainer>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ConditionalCaseContainer>>> GetReader();
