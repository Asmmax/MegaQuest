#include "Containers/ReaderStrategy/ContainerReader.hpp"

template<>
void ContainerBinder<${full_type_name}>::BindImpl(const ContainerBinder::ContainerImplPtr& impl)
{
	BindImplWithCast<${type_name}Container>(impl);
}

template<>
const std::shared_ptr<IContainer<${full_type_name}>>& GlobalContext::GetContainer<${full_type_name}>()
{
	static std::shared_ptr<IContainer<${full_type_name}>> 
		instancePtr = std::make_shared<${type_name}Container>();
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader()
{
	auto container = GlobalContext::GetContainer<${full_type_name}>();
	return std::make_shared<ContainerReader<std::shared_ptr<${full_type_name}>>>(container);
}
