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

template<>
void FactoryBinder<${full_type_name}>::BindImpl(const FactoryBinder::FactoryImplPtr& impl);

template<>
const std::shared_ptr<IFactory<${full_type_name}>>& GlobalContext::GetFactory<${full_type_name}>();

template <>
std::shared_ptr<IReaderStrategy<${full_type_name}>> GetReader();
