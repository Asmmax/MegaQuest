#include "Generated/ICaseContainer_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerGroupImpl>& impl)
{
	BindImplWithCast<ICaseContainerContainer, CaseContainerGroupImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerStateMachineImpl>& impl)
{
	BindImplWithCast<ICaseContainerContainer, CaseContainerStateMachineImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalCaseContainerImpl>& impl)
{
	BindImplWithCast<ICaseContainerContainer, ConditionalCaseContainerImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleCaseContainerImpl>& impl)
{
	BindImplWithCast<ICaseContainerContainer, SimpleCaseContainerImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>>& GlobalContext::GetContainer<QuestCore::ICaseContainer>()
{
	static std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>> 
		instancePtr = std::make_shared<ICaseContainerContainer>("containers");
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ICaseContainer>>> GetReader()
{
	auto container = GlobalContext::GetContainer<QuestCore::ICaseContainer>();
	return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>>(container);
}
