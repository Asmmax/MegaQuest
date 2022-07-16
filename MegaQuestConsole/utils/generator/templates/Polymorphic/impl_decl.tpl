#include "Containers/FactoryImpl.hpp"

using ${type_name}Impl = FactoryImpl<std::shared_ptr<${full_type_name}>
${property_types}
>;

class ${type_name}Impl_Binder
{
public:
    ${type_name}Impl_Binder();

private:
    static ${type_name}Impl_Binder instance;
};

