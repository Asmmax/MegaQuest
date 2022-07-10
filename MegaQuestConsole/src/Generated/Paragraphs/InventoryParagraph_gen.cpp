#include "Generated/Paragraphs/InventoryParagraph_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

//ItemOrder

ItemOrderImpl_Binder ItemOrderImpl_Binder::instance;

ItemOrderImpl_Binder::ItemOrderImpl_Binder()
{
    auto impl = std::make_shared<ItemOrderImpl>(
        CreateProperty<std::shared_ptr<QuestCore::Item>>("item", nullptr)
        , CreateProperty<int>("order", 0)
        );

    FactoryBinder<QuestCore::ItemOrder>().BindImpl("ItemOrder", impl);
}

template<>
template<>
void FactoryBinder<QuestCore::ItemOrder>::BindImpl(const std::string& implName, const std::shared_ptr<ItemOrderImpl>& impl)
{
    BindImplWithCast<ItemOrderFactory, ItemOrderImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<QuestCore::ItemOrder>>& GlobalContext::GetFactory<QuestCore::ItemOrder>()
{
	static std::shared_ptr<IFactory<QuestCore::ItemOrder>>
		instancePtr = std::make_shared<ItemOrderFactory>();
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<QuestCore::ItemOrder>> GetReader()
{
    auto factory = GlobalContext::GetFactory<QuestCore::ItemOrder>();
    return std::make_shared<FactoryReader<QuestCore::ItemOrder>>(factory);
}

//InventoryParagraph

InventoryParagraphImpl_Binder InventoryParagraphImpl_Binder::instance;

InventoryParagraphImpl_Binder::InventoryParagraphImpl_Binder()
{
    auto impl = std::make_shared<InventoryParagraphImpl>(
        InventoryParagraphInitializer(
        )
        , CreateProperty<QuestCore::FormatedString>("prefix", QuestCore::FormatedString())
        , CreateProperty<QuestCore::TextString>("gap", QuestCore::TextString())
        , CreateProperty<QuestCore::FormatedString>("postfix", QuestCore::FormatedString())
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("inventory", nullptr)
        , CreateProperty<std::vector<QuestCore::ItemOrder>>("itemOrders", std::vector<QuestCore::ItemOrder>())
        );

    ContainerBinder<QuestCore::InventoryParagraph>().BindImpl("InventoryParagraph", impl);
    ContainerBinder<QuestCore::IParagraph>().BindImpl("InventoryParagraph", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::InventoryParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryParagraphImpl>& impl)
{
    BindImplWithCast<InventoryParagraphContainer, InventoryParagraphImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::InventoryParagraph>>& GlobalContext::GetContainer<QuestCore::InventoryParagraph>()
{
    static std::shared_ptr<ContainerBase<QuestCore::InventoryParagraph>>
        instancePtr = std::make_shared<InventoryParagraphContainer>("paragraphs");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::InventoryParagraph>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::InventoryParagraph>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::InventoryParagraph>>>(container);
}
