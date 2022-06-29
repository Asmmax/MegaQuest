#include "Generated/Paragraphs/InventoryParagraph_gen.hpp"
#include "Generated/IParagraph_gen.hpp"

//ItemOrder

ItemOrderImpl_Binder ItemOrderImpl_Binder::instance;

ItemOrderImpl_Binder::ItemOrderImpl_Binder()
{
    auto itemContainer = GlobalContext::GetContainer<QuestCore::Item>();
    ContainerReader<std::shared_ptr<QuestCore::Item>> itemReader(itemContainer);

    PrimitiveReader<int> intReader;

    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader<std::shared_ptr<QuestCore::Item>>>
        itemProperty("item", itemReader, nullptr);

    PropertyReader<int, PrimitiveReader<int>>
        orderProperty("order", intReader, 0);

    auto itemOrderImpl = std::make_shared<ItemOrderImpl>(itemProperty, orderProperty);

    if (auto itemOrderFactory = std::dynamic_pointer_cast<ItemOrderFactory>(GlobalContext::GetFactory<QuestCore::ItemOrder>())) {
        itemOrderFactory->SetInheritor<ItemOrderImpl>(
            ReaderImplRecord<ItemOrderImpl>{ "ItemOrder", itemOrderImpl });
    }
}

template<>
const std::shared_ptr<IFactory<QuestCore::ItemOrder>>& GlobalContext::GetFactory<QuestCore::ItemOrder>()
{
	static std::shared_ptr<IFactory<QuestCore::ItemOrder>>
		instancePtr = std::make_shared<ItemOrderFactory>();
	return instancePtr;
}

//InventoryParagraph

InventoryParagraphImpl_Binder InventoryParagraphImpl_Binder::instance;

InventoryParagraphImpl_Binder::InventoryParagraphImpl_Binder()
{
    auto formatedTextFactory = GlobalContext::GetFactory<QuestCore::FormatedString>();
    FactoryReader<QuestCore::FormatedString>
        formatedTextReader(formatedTextFactory);

    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString>
        textFactoryReader(textFactory);

    auto itemOrderFactory = GlobalContext::GetFactory<QuestCore::ItemOrder>();
    FactoryReader<QuestCore::ItemOrder>
        itemOrderReader(itemOrderFactory);

    auto inventoryContainer = GlobalContext::GetContainer<QuestCore::Inventory>();
    ContainerReader<std::shared_ptr<QuestCore::Inventory>>
        inventoryContainerReader(inventoryContainer);

    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>
        prefixReader("prefix", formatedTextReader, QuestCore::FormatedString());

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        gapReader("gap", textFactoryReader, QuestCore::TextString());

    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>
        postfixReader("postfix", formatedTextReader, QuestCore::FormatedString());

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
        inventoryReader("inventory", inventoryContainerReader, nullptr);

    PropertyReader<std::vector<QuestCore::ItemOrder>, FactoryReader<QuestCore::ItemOrder>>
        itemOrdersReader("itemOrders", itemOrderReader, std::vector<QuestCore::ItemOrder>());

    auto inventoryParagraphImpl = std::make_shared<InventoryParagraphImpl>(
        ContainerInitializer<QuestCore::InventoryParagraph>(),
        prefixReader, gapReader, postfixReader, inventoryReader, itemOrdersReader);

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<InventoryParagraphImpl>(
            ReaderImplRecord<InventoryParagraphImpl>{ "InventoryParagraph", inventoryParagraphImpl });
    }
}
