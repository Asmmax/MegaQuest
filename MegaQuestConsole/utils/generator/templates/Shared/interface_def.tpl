#include "Containers/ReaderStrategy/ContainerReader.hpp"

template<>
void ContainerBinder<${full_type_name}>::BindImpl(const ContainerBinder::ContainerImplPtr& impl)
{
	BindImplWithCast<${type_name}Container>(impl);
}

template<>
template<>
std::shared_ptr<IContainer<${full_type_name}>> ContainerFactory<IContainer>::Create<${full_type_name}>()
{
	return std::make_shared<${type_name}Container>();
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader()
{
	auto container = Context::Global().GetContainer<${full_type_name}>();
	return std::make_shared<ContainerReader<std::shared_ptr<${full_type_name}>>>(container);
}
