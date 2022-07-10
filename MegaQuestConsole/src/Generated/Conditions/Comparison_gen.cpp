#include "Generated/Conditions/Comparison_gen.hpp"
#include "Containers/ReaderStrategy/EnumReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

template <>
std::shared_ptr<IReaderStrategy<QuestCore::Operation>> GetReader()
{
    return std::make_shared<EnumReader<QuestCore::Operation>>(std::map<std::string, QuestCore::Operation>{
        { "None", QuestCore::Operation::None },
        { "Less", QuestCore::Operation::Less },
        { "Greater", QuestCore::Operation::Greater },
        { "Equal", QuestCore::Operation::Equal },
        { "NotLess", QuestCore::Operation::NotLess },
        { "NotGreater", QuestCore::Operation::NotGreater },
        { "NotEqual", QuestCore::Operation::NotEqual }
    });
}

ComparisonImpl_Binder ComparisonImpl_Binder::instance;

ComparisonImpl_Binder::ComparisonImpl_Binder()
{
    auto impl = std::make_shared<ComparisonImpl>(
        CreateProperty<std::shared_ptr<QuestCore::Value>>("left", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::Value>>("right", nullptr)
        , CreateProperty<QuestCore::Operation>("op", QuestCore::Operation::None)
        );

    FactoryBinder<std::shared_ptr<QuestCore::Comparison>>().BindImpl("Comparison", impl);
    FactoryBinder<std::shared_ptr<QuestCore::ICondition>>().BindImpl("Comparison", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Comparison>>::BindImpl(const std::string& implName, const std::shared_ptr<ComparisonImpl>& impl)
{
    BindImplWithCast<ComparisonFactory, ComparisonImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Comparison>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Comparison>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Comparison>>>
        instancePtr = std::make_shared<ComparisonFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Comparison>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::Comparison>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::Comparison>>>(factory);
}
