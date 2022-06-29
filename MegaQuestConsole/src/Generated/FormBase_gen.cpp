#include "Generated/FormBase_gen.hpp"

FormBaseImpl_Binder FormBaseImpl_Binder::instance;

FormBaseImpl_Binder::FormBaseImpl_Binder()
{
    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString> textFactoryReader(textFactory);

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        textProperty("text", textFactoryReader, QuestCore::TextString());

    auto formBaseImpl = std::make_shared<FormBaseImpl>(textProperty);

    if (auto formBaseFactory = std::dynamic_pointer_cast<FormBaseFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>())) {
        formBaseFactory->SetInheritor<FormBaseImpl>(
            ReaderImplRecord<FormBaseImpl>{ "FormBase", formBaseImpl });
    }
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>
        instancePtr = std::make_shared<FormBaseFactory>();
    return instancePtr;
}
