#include "Generated/CaseContainers/SimpleCaseContainer_gen.hpp"
#include "Generated/ICaseContainer_gen.hpp"

SimpleCaseContainerImpl_Binder SimpleCaseContainerImpl_Binder::instance;

SimpleCaseContainerImpl_Binder::SimpleCaseContainerImpl_Binder()
{
    auto caseFactory = GlobalContext::GetFactory<QuestCore::Case>();
    FactoryReader<QuestCore::Case>
        caseReader(caseFactory);

    PropertyReader<std::vector<QuestCore::Case>, FactoryReader>
        casesReader("cases", caseReader, std::vector<QuestCore::Case>());

    auto simpleCaseContainerImpl = std::make_shared<SimpleCaseContainerImpl>(
        ContainerInitializer<QuestCore::SimpleCaseContainer>(),
        casesReader);

    if (auto containerContainer = std::dynamic_pointer_cast<ICaseContainerContainer>(GlobalContext::GetContainer<QuestCore::ICaseContainer>())) {
        containerContainer->SetInheritor<SimpleCaseContainerImpl>(
            ReaderImplRecord<SimpleCaseContainerImpl>{ "SimpleCaseContainer", simpleCaseContainerImpl });
    }
}
