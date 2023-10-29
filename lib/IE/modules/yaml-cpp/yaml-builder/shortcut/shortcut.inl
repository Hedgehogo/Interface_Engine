//included into shortcut.hpp

namespace ie {
	template<typename Base, typename Type>
	void inherit(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::add_aliases(aliases);
		YamlBuilder<Base>::template add_type<Type>();
		
		add_to_yaml_builders<Base>();
		add_to_yaml_builders<Type>();
	}
	
	template<typename Base, typename Type, typename... Types>
	void add_type() {
		YamlBuilder<Base>::template add_type<Type>();
		
		add_to_yaml_builders<Base>();
		add_to_yaml_builders<Type>();
		
		add_type<Base, Types...>();
	}
	
	template<typename Base, typename... Types>
	void add_type(const std::vector<std::string>& aliases) {
		YamlBuilder<Base>::add_aliases(aliases);
		add_type<Base, Types...>();
	}
	
	template<typename Type, typename Base, typename... Bases>
	void add_base() {
		YamlBuilder<Base>::template add_type<Type>();
		
		add_to_yaml_builders<Base>();
		add_to_yaml_builders<Type>();
		
		add_base<Type, Bases...>();
	}
	
	template<typename Type, typename... Bases>
	void add_base(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::add_aliases(aliases);
		add_base<Type, Bases...>();
	}
	
	template<typename Type>
	void add_aliases(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::add_aliases(aliases);
	}
	
	template<typename Type>
	void add_determine(const detail::DetermineTypeFunc& function) {
		YamlBuilder<Type>::add_determine(function);
	}
	
	template<typename Type>
	void add_determine(const detail::SimpleDetermineTypeFunc& function) {
		YamlBuilder<Type>::add_determine(function);
	}
	
	template<typename Base>
	void add_func(detail::FuncYamlBuilder::BuildFunc<Base> function, std::vector<std::string> names) {
		YamlBuilder<Base>::add_type(function, names);
	}
}