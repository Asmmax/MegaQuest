#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/Context.hpp"

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> Context::GetReader()
{
	auto container = GetContainer<${full_type_name}>();
	return std::make_shared<ContainerReader<std::shared_ptr<${full_type_name}>>>(container);
}
