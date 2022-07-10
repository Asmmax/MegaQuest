#pragma once
#include "Actions/Clearing.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ClearingInitializer = ContainerInitializer<QuestCore::Clearing>;

using ClearingImpl = ContainerImpl<QuestCore::Clearing,
    ClearingInitializer,
    std::shared_ptr<QuestCore::Inventory>
>;

class ClearingImpl_Binder
{
public:
    ClearingImpl_Binder();

private:
    static ClearingImpl_Binder instance;
};

using ClearingContainer = Container<QuestCore::Clearing, ClearingImpl>;

template<>
template<>
void ContainerBinder<QuestCore::Clearing>::BindImpl(const std::string& implName, const std::shared_ptr<ClearingImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::Clearing>>& GlobalContext::GetContainer<QuestCore::Clearing>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Clearing>>> GetReader();
