#include "Containers/FactoryImpl.hpp"
#include "Containers/FactoryImplBase.hpp"

using ${type_name}ImplBases = FactoryImplBases<std::shared_ptr<${full_type_name}>
${all_bases}
>;

using ${type_name}Impl = FactoryImpl<std::shared_ptr<${full_type_name}>
, ${type_name}ImplBases
${property_types}
>;

class ${type_name}Impl_Binder
{
public:
    ${type_name}Impl_Binder();

private:
    static ${type_name}Impl_Binder instance;
};

