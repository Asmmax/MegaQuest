${children_include}

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Container = Container<${full_type_name}
${impl_names}
>;

${bind_impls}

template<>
const std::shared_ptr<ContainerBase<${full_type_name}>>& GlobalContext::GetContainer<${full_type_name}>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader();
