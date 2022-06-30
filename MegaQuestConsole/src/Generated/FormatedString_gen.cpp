#include "Generated/FormatedString_gen.hpp"

FormatedStringImpl_Binder FormatedStringImpl_Binder::instance;

FormatedStringImpl_Binder::FormatedStringImpl_Binder()
{
    auto formBaseFactory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>();
    FactoryReader<std::shared_ptr<QuestCore::FormBase>> formBaseReader(formBaseFactory);

    PropertyReader<std::vector<std::shared_ptr<QuestCore::FormBase>>, FactoryReader>
        formsProperty("forms", formBaseReader, std::vector<std::shared_ptr<QuestCore::FormBase>>());

    auto formatedStringImpl = std::make_shared<FormatedStringImpl>(formsProperty);

    if (auto formatedStringFactory = std::dynamic_pointer_cast<FormatedStringFactory>(GlobalContext::GetFactory<QuestCore::FormatedString>())) {
        formatedStringFactory->SetInheritor<FormatedStringImpl>(
            ReaderImplRecord<FormatedStringImpl>{ "FormatedString", formatedStringImpl });
    }
}

template<>
const std::shared_ptr<IFactory<QuestCore::FormatedString>>& GlobalContext::GetFactory<QuestCore::FormatedString>()
{
    static std::shared_ptr<IFactory<QuestCore::FormatedString>>
        instancePtr = std::make_shared<FormatedStringFactory>();
    return instancePtr;
}
