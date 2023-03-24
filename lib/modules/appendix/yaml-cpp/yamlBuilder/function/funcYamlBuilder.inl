//include into functionBuilder.hpp

namespace ui::detail {
	template <typename Type>
	FuncYamlBuilder &FuncYamlBuilder::addBuilder(FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases) {
		return builders.emplace_back([function](const YAML::Node &node, void *&object) { return function(node, reinterpret_cast<Type*&>(object)); }, aliases);
	}
}