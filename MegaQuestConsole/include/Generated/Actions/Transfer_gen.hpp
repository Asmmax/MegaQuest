#pragma once
#include "Actions/Transfer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using TransferInitializer = ContainerInitializer<QuestCore::Transfer>;

using TransferImpl = ContainerImpl<QuestCore::Transfer,
    TransferInitializer,
    std::shared_ptr<QuestCore::Inventory>,
    std::shared_ptr<QuestCore::Inventory>,
    std::vector<QuestCore::ItemRecord>
>;

class TransferImpl_Binder
{
public:
    TransferImpl_Binder();

private:
    static TransferImpl_Binder instance;
};

using TransferContainer = Container<QuestCore::Transfer, TransferImpl>;

template<>
template<>
void ContainerBinder<QuestCore::Transfer>::BindImpl(const std::string& implName, const std::shared_ptr<TransferImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::Transfer>>& GlobalContext::GetContainer<QuestCore::Transfer>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Transfer>>> GetReader();
