#include "Generated/IAction_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerSwitchingImpl>& impl)
{
	BindImplWithCast<IActionContainer, CaseContainerSwitchingImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<ClearingImpl>& impl)
{
	BindImplWithCast<IActionContainer, ClearingImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<CopyingImpl>& impl)
{
	BindImplWithCast<IActionContainer, CopyingImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphSwitchingImpl>& impl)
{
	BindImplWithCast<IActionContainer, ParagraphSwitchingImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<TransferImpl>& impl)
{
	BindImplWithCast<IActionContainer, TransferImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::IAction>>& GlobalContext::GetContainer<QuestCore::IAction>()
{
	static std::shared_ptr<ContainerBase<QuestCore::IAction>>
		instancePtr = std::make_shared<IActionContainer>("actions");
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::IAction>>> GetReader()
{
	auto container = GlobalContext::GetContainer<QuestCore::IAction>();
	return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::IAction>>>(container);
}
