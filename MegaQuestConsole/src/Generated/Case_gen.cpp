#include "Generated/Case_gen.hpp"

CaseImpl_Binder CaseImpl_Binder::instance;

CaseImpl_Binder::CaseImpl_Binder()
{
    auto textFactory = GlobalContext::GetFactory<QuestCore::TextString>();
    FactoryReader<QuestCore::TextString> textFactoryReader(textFactory);

    auto actionContainer = GlobalContext::GetContainer<QuestCore::IAction>();
    ContainerReader<std::shared_ptr<QuestCore::IAction>> actionReader(actionContainer);

    PropertyReader<QuestCore::TextString, FactoryReader>
        nameProperty("name", textFactoryReader, QuestCore::TextString());

    PropertyReader<std::vector<std::shared_ptr<QuestCore::IAction>>, ContainerReader>
        actionsProperty("actions", actionReader, std::vector<std::shared_ptr<QuestCore::IAction>>());

    auto caseImpl = std::make_shared<CaseImpl>(nameProperty, actionsProperty);

    if (auto caseFactory = std::dynamic_pointer_cast<CaseFactory>(GlobalContext::GetFactory<QuestCore::Case>())) {
        caseFactory->SetInheritor<CaseImpl>(
            ReaderImplRecord<CaseImpl>{ "Case", caseImpl });
    }
}

template<>
const std::shared_ptr<IFactory<QuestCore::Case>>& GlobalContext::GetFactory<QuestCore::Case>()
{
    static std::shared_ptr<IFactory<QuestCore::Case>>
        instancePtr = std::make_shared<CaseFactory>();
    return instancePtr;
}
