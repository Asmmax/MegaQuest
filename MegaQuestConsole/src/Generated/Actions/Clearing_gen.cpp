#include "Generated/Actions/Clearing_gen.hpp"
#include "Generated/IAction_gen.hpp"

ClearingImpl_Binder ClearingImpl_Binder::instance;

ClearingImpl_Binder::ClearingImpl_Binder()
{
    auto inventoryContainer = GlobalContext::GetContainer<QuestCore::Inventory>();

    ContainerReader<std::shared_ptr<QuestCore::Inventory>>
        inventoryReader(inventoryContainer);

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
        inventoryProperty("inventory", inventoryReader, nullptr);

    auto clearingImpl = std::make_shared<ClearingImpl>(ContainerInitializer<QuestCore::Clearing>(), inventoryProperty);

    if (auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(GlobalContext::GetContainer<QuestCore::IAction>())) {
        actionContainer->SetInheritor<ClearingImpl>(
            ReaderImplRecord<ClearingImpl>{ "Clearing", clearingImpl });
    }
}
