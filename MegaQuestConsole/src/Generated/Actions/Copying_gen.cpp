#include "Generated/Actions/Copying_gen.hpp"
#include "Generated/IAction_gen.hpp"

CopyingImpl_Binder CopyingImpl_Binder::instance;

CopyingImpl_Binder::CopyingImpl_Binder()
{
    auto inventoryContainer = GlobalContext::GetContainer<QuestCore::Inventory>();

    ContainerReader<std::shared_ptr<QuestCore::Inventory>>
        inventoryReader(inventoryContainer);

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
        inventorySourceProperty("source", inventoryReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
        inventoryTargetProperty("target", inventoryReader, nullptr);

    auto copyingImpl = std::make_shared<CopyingImpl>(ContainerInitializer<QuestCore::Copying>(),
        inventorySourceProperty, inventoryTargetProperty);

    if (auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(GlobalContext::GetContainer<QuestCore::IAction>())) {
        actionContainer->SetInheritor<CopyingImpl>(
            ReaderImplRecord<CopyingImpl>{ "Copying", copyingImpl });
    }
}
