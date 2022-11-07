#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ContainerImplBase.hpp"

using ${type_name}ImplBases = ContainerImplBases<${full_type_name}
${all_bases}
>;

using ${type_name}Initializer = ContainerInitializer<${full_type_name}
${method_arg_types}
>;

using ${type_name}Impl = ContainerImpl<${full_type_name}
, ${type_name}ImplBases
, ${type_name}Initializer
${property_types}
>;
