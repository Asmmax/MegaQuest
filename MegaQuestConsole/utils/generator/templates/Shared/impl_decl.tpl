#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

using ${type_name}Initializer = ContainerInitializer<${full_type_name}
${method_arg_types}
>;

using ${type_name}Impl = ContainerImpl<${full_type_name}
, ${type_name}Initializer
${property_types}
>;

class ${type_name}Impl_Binder
{
public:
    ${type_name}Impl_Binder();

private:
    static ${type_name}Impl_Binder instance;
};
