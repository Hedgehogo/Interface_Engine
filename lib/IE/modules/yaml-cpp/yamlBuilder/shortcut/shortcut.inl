//included into shortcut.hpp

#include "../../modules/exception/yamlBuilderDoesNotExist/yamlBuilderDoesNotExistException.hpp"

namespace ie {
	template<typename Base, typename Type>
	void inherit(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::addAliases(aliases);
		YamlBuilder<Base>::template addType<Type>();
		
		addToYamlBuilders<Base>();
		addToYamlBuilders<Type>();
	}
	
	template<typename T>
	void inherit(std::string baseTypeName, const std::vector<std::string>& aliases){
		YamlBuilder<T>::addAliases(aliases);
		if (detail::BaseYamlBuilder* base = detail::yamlBuilders[baseTypeName]; base)
			detail::yamlBuilders[baseTypeName]->addType(&YamlBuilder<T>::builder);
		else
			throw YamlBuilderDoesNotExistException{baseTypeName};
		addToYamlBuilders<T>();
	}
	
	template<typename Base, typename Type, typename... Types>
	void addType() {
		YamlBuilder<Base>::template addType<Type>();
		
		addToYamlBuilders<Base>();
		addToYamlBuilders<Type>();
		
		addType<Base, Types...>();
	}
	
	template<typename Base, typename... Types>
	void addType(const std::vector<std::string>& aliases) {
		YamlBuilder<Base>::addAliases(aliases);
		addType<Base, Types...>();
	}
	
	template<typename Type, typename Base, typename... Bases>
	void addBase() {
		YamlBuilder<Base>::template addType<Type>();
		
		addToYamlBuilders<Base>();
		addToYamlBuilders<Type>();
		
		addBase<Type, Bases...>();
	}
	
	template<typename Type, typename... Bases>
	void addBase(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::addAliases(aliases);
		addBase<Type, Bases...>();
	}
	
	template<typename Type>
	void addAliases(const std::vector<std::string>& aliases) {
		YamlBuilder<Type>::addAliases(aliases);
	}
	
	template<typename Type>
	void addDetermine(const detail::DetermineTypeFunc& function) {
		YamlBuilder<Type>::addDetermine(function);
	}
	
	template<typename Type>
	void addDetermine(const detail::SimpleDetermineTypeFunc& function) {
		YamlBuilder<Type>::addDetermine(function);
	}
	
	template<typename Base>
	void addFunc(detail::FuncYamlBuilder::BuildFunc<Base> function, std::vector<std::string> names) {
		YamlBuilder<Base>::addType(function, names);
	}
}