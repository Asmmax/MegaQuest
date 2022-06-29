#include "Generated/TextString_gen.hpp"

TextStringImpl_Binder TextStringImpl_Binder::instance;

TextStringImpl_Binder::TextStringImpl_Binder()
{
    PrimitiveReader<std::string> stringReader;

    PropertyReader<std::string, PrimitiveReader<std::string>>
        u8Property("u8", stringReader, std::string());

    auto textStringImpl = std::make_shared<TextStringImpl>(u8Property);

    if (auto textStringFactory = std::dynamic_pointer_cast<TextStringFactory>(GlobalContext::GetFactory<QuestCore::TextString>())) {
        textStringFactory->SetInheritor<TextStringImpl>(
            ReaderImplRecord<TextStringImpl>{ "TextString", textStringImpl });
    }
}

template<>
const std::shared_ptr<IFactory<QuestCore::TextString>>& GlobalContext::GetFactory<QuestCore::TextString>()
{
    static std::shared_ptr<IFactory<QuestCore::TextString>>
        instancePtr = std::make_shared<TextStringFactory>();
    return instancePtr;
}
