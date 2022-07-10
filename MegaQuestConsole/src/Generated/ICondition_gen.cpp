#include "Generated/ICondition_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::ICondition>>::BindImpl(const std::string& implName, const std::shared_ptr<ComparisonImpl>& impl)
{
	BindImplWithCast<IConditionFactory, ComparisonImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>()
{
	static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>
		instancePtr = std::make_shared<IConditionFactory>();
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ICondition>>> GetReader()
{
	auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>();
	return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::ICondition>>>(factory);
}
