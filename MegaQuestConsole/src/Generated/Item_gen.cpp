#include "Generated/Item_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ItemImpl_Binder ItemImpl_Binder::instance;

ItemImpl_Binder::ItemImpl_Binder()
{
    auto impl = std::make_shared<ItemImpl>(
        ItemInitializer(
        )
        , CreateProperty<std::string>("name", std::string())
        , CreateProperty<QuestCore::FormatedString>("text", QuestCore::FormatedString())
        , CreateProperty<bool>("isNullable", false)
        );

    ContainerBinder<QuestCore::Item>().BindImpl("Item", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::Item>::BindImpl(const std::string& implName, const std::shared_ptr<ItemImpl>& impl)
{
    BindImplWithCast<ItemContainer, ItemImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Item>>& GlobalContext::GetContainer<QuestCore::Item>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Item>>
        instancePtr = std::make_shared<ItemContainer>("items");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Item>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::Item>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::Item>>>(container);
}
