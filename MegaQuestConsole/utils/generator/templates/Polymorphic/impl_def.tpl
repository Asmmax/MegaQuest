${dependencies}
#include "Containers/Context.hpp"

${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>("${type_name}"
${properties}
        );

    Context::Global().GetFactory<std::shared_ptr<${full_type_name}>>()->AddInheritor(impl);
	${factory_binder_impls}
}
