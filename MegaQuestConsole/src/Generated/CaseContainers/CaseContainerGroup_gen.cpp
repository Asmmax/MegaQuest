#include "Generated/CaseContainers/CaseContainerGroup_gen.hpp"
#include "Generated/ICaseContainer_gen.hpp"

CaseContainerGroupImpl_Binder CaseContainerGroupImpl_Binder::instance;

CaseContainerGroupImpl_Binder::CaseContainerGroupImpl_Binder()
{
    auto iCaseContainerContainer = GlobalContext::GetContainer<QuestCore::ICaseContainer>();

    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>
        caseContainerReader(iCaseContainerContainer);

    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICaseContainer>>, ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>>
        childrenReader("children", caseContainerReader, std::vector<std::shared_ptr<QuestCore::ICaseContainer>>());

    auto caseContainerGroupImpl = std::make_shared<CaseContainerGroupImpl>(
        ContainerInitializer<QuestCore::CaseContainerGroup>(),
        childrenReader);

    if (auto containerContainer = std::dynamic_pointer_cast<ICaseContainerContainer>(GlobalContext::GetContainer<QuestCore::ICaseContainer>())) {
        containerContainer->SetInheritor<CaseContainerGroupImpl>(
            ReaderImplRecord<CaseContainerGroupImpl>{ "CaseContainerGroup", caseContainerGroupImpl });
    }
}
