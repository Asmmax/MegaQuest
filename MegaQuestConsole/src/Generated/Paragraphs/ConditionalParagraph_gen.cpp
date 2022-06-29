#include "Generated/Paragraphs/ConditionalParagraph_gen.hpp"
#include "Generated/IParagraph_gen.hpp"

ConditionalParagraphImpl_Binder ConditionalParagraphImpl_Binder::instance;

ConditionalParagraphImpl_Binder::ConditionalParagraphImpl_Binder()
{
    auto iParagraphContainer = GlobalContext::GetContainer<QuestCore::IParagraph>();
    ContainerReader<std::shared_ptr<QuestCore::IParagraph>>
        paragraphReader(iParagraphContainer);

    auto iConditionFactory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>();
    FactoryReader<std::shared_ptr<QuestCore::ICondition>>
        conditionReader(iConditionFactory);

    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
        thenParagraphReader("thenParagraph", paragraphReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
        elseParagraphReader("elseParagraph", paragraphReader, nullptr);

    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader<std::shared_ptr<QuestCore::ICondition>>>
        conditionsReader("conditions", conditionReader, std::vector<std::shared_ptr<QuestCore::ICondition>>());

    auto conditionalParagraphImpl = std::make_shared<ConditionalParagraphImpl>(
        ContainerInitializer<QuestCore::ConditionalParagraph>(),
        thenParagraphReader, elseParagraphReader, conditionsReader);

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<ConditionalParagraphImpl>(
            ReaderImplRecord<ConditionalParagraphImpl>{ "ConditionalParagraph", conditionalParagraphImpl });
    }
}
