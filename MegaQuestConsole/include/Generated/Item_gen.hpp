#pragma once

#include "Item.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/ContainerInitializer.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

//Item

using ItemInitializer = ContainerInitializer<QuestCore::Item>;

using ItemImpl = ContainerImpl<QuestCore::Item,
    ItemInitializer,
    std::string,
    QuestCore::FormatedString,
    bool
>;

class ItemImpl_Binder
{
public:
    ItemImpl_Binder();

private:
    static ItemImpl_Binder instance;
};

using ItemContainer = Container<QuestCore::Item, ItemImpl>;

template<>
template<>
void ContainerBinder<QuestCore::Item>::BindImpl(const std::string& implName, const std::shared_ptr<ItemImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::Item>>& GlobalContext::GetContainer<QuestCore::Item>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Item>>> GetReader();
