${dependencies}
#include "Containers/GlobalRootReader.hpp"
#include "Containers/Context.hpp"

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

	Context::Global().GetContainer<${full_type_name}>()->AddInheritor(impl);
	${container_binder_impls}
}

