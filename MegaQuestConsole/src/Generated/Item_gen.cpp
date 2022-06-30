#include "Generated/Item_gen.hpp"

ItemImpl_Binder ItemImpl_Binder::instance;

ItemImpl_Binder::ItemImpl_Binder()
{
    auto formatedTextFactory = GlobalContext::GetFactory<QuestCore::FormatedString>();
    FactoryReader<QuestCore::FormatedString> formatedTextReader(formatedTextFactory);

    PrimitiveReader<std::string> stringReader;
    PrimitiveReader<bool> boolReader;

    PropertyReader<std::string, PrimitiveReader>
        nameProperty("name", stringReader, std::string());

    PropertyReader<QuestCore::FormatedString, FactoryReader>
        textProperty("text", formatedTextReader, QuestCore::FormatedString());

    PropertyReader<bool, PrimitiveReader>
        isNullableProperty("isNullable", boolReader, false);

    auto itemImpl = std::make_shared<ItemImpl>(ContainerInitializer<QuestCore::Item>(),
        nameProperty, textProperty, isNullableProperty);

    if (auto itemContainer = std::dynamic_pointer_cast<ItemContainer>(GlobalContext::GetContainer<QuestCore::Item>())) {
        itemContainer->SetInheritor<ItemImpl>(
            ReaderImplRecord<ItemImpl>{ "Item", itemImpl });
    }
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Item>>& GlobalContext::GetContainer<QuestCore::Item>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Item>>
        instancePtr = std::make_shared<ItemContainer>("items");
    return instancePtr;
}
