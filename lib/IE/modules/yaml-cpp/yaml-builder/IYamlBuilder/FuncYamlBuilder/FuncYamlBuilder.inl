//include into function_builder.hpp

namespace ie::detail {
	template<typename Type>
	FuncYamlBuilder& FuncYamlBuilder::add_builder(FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases) {
		return builders_.emplace_back([function](const YAML::Node& node, void*& object) {
			return function(node, reinterpret_cast<Type*&>(object));
		}, aliases);
	}
}