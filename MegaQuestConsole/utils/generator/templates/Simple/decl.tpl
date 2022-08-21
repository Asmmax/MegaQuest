#include "Containers/FactoryImpl.hpp"
#include "Containers/FactoryImplBase.hpp"

using ${type_name}ImplBases = FactoryImplBases<${full_type_name}
${all_bases}
>;

using ${type_name}Impl = FactoryImpl<${full_type_name}
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

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Factory = Factory<${full_type_name}>;

DECLARE_FACTORY_BIND_IMPL(${full_type_name})
DECLARE_FACTORY(${full_type_name})
DECLARE_READER(${full_type_name})
