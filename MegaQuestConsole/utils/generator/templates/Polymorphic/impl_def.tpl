${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>(
${properties}
        );

    FactoryBinder<std::shared_ptr<${full_type_name}>>().BindImpl("${type_name}", impl);
	${factory_binder_impls}
}
