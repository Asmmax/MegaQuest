#include "Generated/CaseContainers/ConditionalCaseContainer_gen.hpp"
#include "Generated/ICaseContainer_gen.hpp"

ConditionalCaseContainerImpl_Binder ConditionalCaseContainerImpl_Binder::instance;

ConditionalCaseContainerImpl_Binder::ConditionalCaseContainerImpl_Binder()
{
    auto iCaseContainerContainer = GlobalContext::GetContainer<QuestCore::ICaseContainer>();

    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>
        caseContainerReader(iCaseContainerContainer);

    auto iConditionFactory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>();

    FactoryReader<std::shared_ptr<QuestCore::ICondition>>
        conditionReader(iConditionFactory);

    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>
        thenContainerReader("thenContainer", caseContainerReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>
        elseContainerReader("elseContainer", caseContainerReader, nullptr);

    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader>
        conditionsReader("conditions", conditionReader, std::vector<std::shared_ptr<QuestCore::ICondition>>());

    auto conditionalCaseContainerImpl = std::make_shared<ConditionalCaseContainerImpl>(
        ContainerInitializer<QuestCore::ConditionalCaseContainer>(),
        thenContainerReader, elseContainerReader, conditionsReader);

    if (auto containerContainer = std::dynamic_pointer_cast<ICaseContainerContainer>(GlobalContext::GetContainer<QuestCore::ICaseContainer>())) {
        containerContainer->SetInheritor<ConditionalCaseContainerImpl>(
            ReaderImplRecord<ConditionalCaseContainerImpl>{ "ConditionalCaseContainer", conditionalCaseContainerImpl });
    }
}
