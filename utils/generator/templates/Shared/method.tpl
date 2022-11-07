context.CreateMethod<${full_type_name},${full_arg_type_name}>("${arg_name}", ${full_arg_type_name}(), 
    [](const std::shared_ptr<${full_type_name}>& element, const ${full_arg_type_name}& arg) {
        element->${method_name}(arg);
    })