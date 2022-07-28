#include "Containers/GlobalRootReader.hpp"

${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>(
		"${shared_name}"
		,"${type_name}"
        ,${type_name}Initializer(
${methods}
        )
${properties}
        );
		
	GlobalRootReader::Instance().AddContainer(impl);

    ContainerBinder<${full_type_name}>().BindImpl(impl);
	${container_binder_impls}
}

