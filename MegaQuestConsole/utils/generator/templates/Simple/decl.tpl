#include "Containers/FactoryImpl.hpp"

using ${type_name}Impl = FactoryImpl<${full_type_name}
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

using ${type_name}Factory = Factory<${full_type_name}
, ${type_name}Impl
>;

template<>
template<>
void FactoryBinder<${full_type_name}>::BindImpl(const std::string& implName, const std::shared_ptr<${type_name}Impl>& impl);

template<>
const std::shared_ptr<IFactory<${full_type_name}>>& GlobalContext::GetFactory<${full_type_name}>();

template <>
std::shared_ptr<IReaderStrategy<${full_type_name}>> GetReader();
