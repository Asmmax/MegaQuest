#include "Generated/Paragraphs/TextParagraph_gen.hpp"
#include "Generated/IParagraph_gen.hpp"

TextParagraphImpl_Binder TextParagraphImpl_Binder::instance;

TextParagraphImpl_Binder::TextParagraphImpl_Binder()
{
    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString>
        textFactoryReader(textFactory);

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        textReader("text", textFactoryReader, QuestCore::TextString());

    auto textParagraphImpl = std::make_shared<TextParagraphImpl>(
        ContainerInitializer<QuestCore::TextParagraph>(),
        textReader);

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<TextParagraphImpl>(
            ReaderImplRecord<TextParagraphImpl>{ "TextParagraph", textParagraphImpl });
    }
}
