#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Container = Container<${full_type_name}>;

template<>
void ContainerBinder<${full_type_name}>::BindImpl(const ContainerBinder::ContainerImplPtr& impl);

template<>
const std::shared_ptr<IContainer<${full_type_name}>>& GlobalContext::GetContainer<${full_type_name}>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader();
