#include "Generated/Paragraphs/ParagraphGroup_gen.hpp"
#include "Generated/IParagraph_gen.hpp"

ParagraphGroupImpl_Binder ParagraphGroupImpl_Binder::instance;

ParagraphGroupImpl_Binder::ParagraphGroupImpl_Binder()
{
    auto iParagraphContainer = GlobalContext::GetContainer<QuestCore::IParagraph>();
    ContainerReader<std::shared_ptr<QuestCore::IParagraph>>
        paragraphReader(iParagraphContainer);

    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString>
        textFactoryReader(textFactory);

    PropertyReader<std::vector<std::shared_ptr<QuestCore::IParagraph>>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
        childrenReader("children", paragraphReader, std::vector<std::shared_ptr<QuestCore::IParagraph>>());

    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
        gapReader("gap", textFactoryReader, QuestCore::TextString());

    auto paragraphGroupImpl = std::make_shared<ParagraphGroupImpl>(
        ContainerInitializer<QuestCore::ParagraphGroup>(),
        childrenReader, gapReader);

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<ParagraphGroupImpl>(
            ReaderImplRecord<ParagraphGroupImpl>{ "ParagraphGroup", paragraphGroupImpl });
    }
}
