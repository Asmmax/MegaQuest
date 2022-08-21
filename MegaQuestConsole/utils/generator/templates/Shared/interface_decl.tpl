#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Container = Container<${full_type_name}>;

DECLARE_CONTAINER_BIND_IMPL(${full_type_name})
DECLARE_CONTAINER(${full_type_name})
DECLARE_READER(std::shared_ptr<${full_type_name}>)
