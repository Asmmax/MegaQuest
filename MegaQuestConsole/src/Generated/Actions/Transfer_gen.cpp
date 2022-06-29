#include "Generated/Actions/Transfer_gen.hpp"
#include "Generated/IAction_gen.hpp"

TransferImpl_Binder TransferImpl_Binder::instance;

TransferImpl_Binder::TransferImpl_Binder()
{
    auto itemRecordFactory = GlobalContext::GetFactory<QuestCore::ItemRecord>();
    FactoryReader<QuestCore::ItemRecord>
        itemRecordReader(itemRecordFactory);

    auto inventoryContainer = GlobalContext::GetContainer<QuestCore::Inventory>();
    ContainerReader<std::shared_ptr<QuestCore::Inventory>>
        inventoryReader(inventoryContainer);

    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader<QuestCore::ItemRecord>>
        itemsProperty("items", itemRecordReader, std::vector<QuestCore::ItemRecord>());

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
        inventorySourceProperty("source", inventoryReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
        inventoryTargetProperty("target", inventoryReader, nullptr);

    auto transferImpl = std::make_shared<TransferImpl>(ContainerInitializer<QuestCore::Transfer>(),
        inventorySourceProperty, inventoryTargetProperty, itemsProperty);

    if (auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(GlobalContext::GetContainer<QuestCore::IAction>())) {
        actionContainer->SetInheritor<TransferImpl>(
            ReaderImplRecord<TransferImpl>{ "Transfer", transferImpl });
    }
}
