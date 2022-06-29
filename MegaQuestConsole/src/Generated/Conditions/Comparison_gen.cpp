#include "Generated/Conditions/Comparison_gen.hpp"
#include "Generated/ICondition_gen.hpp"

ComparisonImpl_Binder ComparisonImpl_Binder::instance;

ComparisonImpl_Binder::ComparisonImpl_Binder()
{
    auto valueFactory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>();
    FactoryReader<std::shared_ptr<QuestCore::Value>> valueReader(valueFactory);

    EnumReader<QuestCore::Operation> operationEnumReader(std::map<std::string, QuestCore::Operation>{
        { "None", QuestCore::Operation::None },
        { "Less", QuestCore::Operation::Less },
        { "Greater", QuestCore::Operation::Greater },
        { "Equal", QuestCore::Operation::Equal },
        { "NotLess", QuestCore::Operation::NotLess },
        { "NotGreater", QuestCore::Operation::NotGreater },
        { "NotEqual", QuestCore::Operation::NotEqual }
    });

    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>
        leftProperty("left", valueReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>
        rightProperty("right", valueReader, nullptr);

    PropertyReader<QuestCore::Operation, EnumReader<QuestCore::Operation>>
        operationReader("op", operationEnumReader, QuestCore::Operation::None);

    auto comparisonImpl = std::make_shared<ComparisonImpl>(leftProperty, rightProperty, operationReader);

    if (auto conditionContainer = std::dynamic_pointer_cast<IConditionFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>())) {
        conditionContainer->SetInheritor<ComparisonImpl>(
            ReaderImplRecord<ComparisonImpl>{ "Comparison", comparisonImpl });
    }
}
