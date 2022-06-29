#include "Generated/Forms_gen.hpp"
#include "Generated/FormBase_gen.hpp"

//SpecificForm

SpecificFormImpl_Binder SpecificFormImpl_Binder::instance;

SpecificFormImpl_Binder::SpecificFormImpl_Binder()
{
    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
	FactoryReader<QuestCore::TextString> textFactoryReader(textFactory);

    PrimitiveReader<int> intReader;

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        textProperty("text", textFactoryReader, QuestCore::TextString());

    PropertyReader<std::vector<int>, PrimitiveReader<int>>
        countsProperty("counts", intReader, std::vector<int>());

    auto specificFormImpl = std::make_shared<SpecificFormImpl>(countsProperty, textProperty);

    if (auto formBaseFactory = std::dynamic_pointer_cast<FormBaseFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>())) {
        formBaseFactory->SetInheritor<SpecificFormImpl>(
            ReaderImplRecord<SpecificFormImpl>{ "SpecificForm", specificFormImpl });
    }
}

//TailForm

TailFormImpl_Binder TailFormImpl_Binder::instance;

TailFormImpl_Binder::TailFormImpl_Binder()
{
    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString> textFactoryReader(textFactory);

    PrimitiveReader<int> intReader;

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        textProperty("text", textFactoryReader, QuestCore::TextString());

    PropertyReader<int, PrimitiveReader<int>>
        notationProperty("notation", intReader, 0);

    PropertyReader<std::vector<int>, PrimitiveReader<int>>
        digitsProperty("digits", intReader, std::vector<int>());

    auto tailFormImpl = std::make_shared<TailFormImpl>(notationProperty, digitsProperty, textProperty);

    if (auto formBaseFactory = std::dynamic_pointer_cast<FormBaseFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>())) {
        formBaseFactory->SetInheritor<TailFormImpl>(
            ReaderImplRecord<TailFormImpl>{ "TailForm", tailFormImpl });
    }
}
