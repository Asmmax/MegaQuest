template<>
template<>
void FactoryBinder<std::shared_ptr<${full_type_name}>>::BindImpl(const std::string& implName, const std::shared_ptr<${impl_type_name}Impl>& impl)
{
    BindImplWithCast<${type_name}Factory, ${impl_type_name}Impl>(implName, impl);
}
