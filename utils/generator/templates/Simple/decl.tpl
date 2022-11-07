#include "Containers/FactoryImpl.hpp"
#include "Containers/FactoryImplBase.hpp"

using ${type_name}ImplBases = FactoryImplBases<${full_type_name}
${all_bases}
>;

using ${type_name}Impl = FactoryImpl<${full_type_name}
, ${type_name}ImplBases
${property_types}
>;

#include "Containers/Context.hpp"

DECLARE_READER(${full_type_name})
