#include "Containers/ReaderStrategy/ContainerReader.hpp"

${bind_impls}

template<>
const std::shared_ptr<ContainerBase<${full_type_name}>>& GlobalContext::GetContainer<${full_type_name}>()
{
	static std::shared_ptr<ContainerBase<${full_type_name}>> 
		instancePtr = std::make_shared<${type_name}Container>("${shared_name}");
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader()
{
	auto container = GlobalContext::GetContainer<${full_type_name}>();
	return std::make_shared<ContainerReader<std::shared_ptr<${full_type_name}>>>(container);
}
