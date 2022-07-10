#pragma once
#include "Actions/Copying.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using CopyingInitializer = ContainerInitializer<QuestCore::Copying>;

using CopyingImpl = ContainerImpl<QuestCore::Copying,
    CopyingInitializer,
    std::shared_ptr<QuestCore::Inventory>,
    std::shared_ptr<QuestCore::Inventory>
>;

class CopyingImpl_Binder
{
public:
    CopyingImpl_Binder();

private:
    static CopyingImpl_Binder instance;
};

using CopyingContainer = Container<QuestCore::Copying, CopyingImpl>;

template<>
template<>
void ContainerBinder<QuestCore::Copying>::BindImpl(const std::string& implName, const std::shared_ptr<CopyingImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::Copying>>& GlobalContext::GetContainer<QuestCore::Copying>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Copying>>> GetReader();
