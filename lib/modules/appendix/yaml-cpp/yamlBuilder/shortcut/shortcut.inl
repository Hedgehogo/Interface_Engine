//included into shortcut.hpp

namespace ui {
	template<typename Base, typename Type>
	void addType(std::vector<std::string> aliases) {
		YamlBuilder<Base>::template add<Type>(aliases);
	}
	
	template<typename Type>
	void addBase(const std::vector<std::string> &aliases) {}
	
	template<typename Type, typename BaseType, typename... BaseTypes>
	void addBase(const std::vector<std::string> &aliases) {
		YamlBuilder<BaseType>::template add<Type>(aliases);
		addBase<Type, BaseTypes...>(aliases);
	}
	
	template<typename Base, typename Type>
	void addSubtype() {
		YamlBuilder<Base>::template addSubtype<Type>();
	}
	
	template<typename Subtype>
	void addBaseSub() {}
	
	template<typename Subtype, typename BaseType, typename... BaseTypes>
	void addBaseSub() {
		YamlBuilder<BaseType>::template addSubtype<Subtype>();
		addBaseSub<Subtype, BaseTypes...>();
	}
	
	template<typename Type>
	void addDetermine(const detail::DetermineTypeFunc &function) {
		YamlBuilder<Type>::addDetermine(function);
	}
	
	template<typename FirstType, typename SecondType, typename... BaseTypes>
	void addDetermine(const detail::DetermineTypeFunc &function) {
		YamlBuilder<FirstType>::addDetermine(function);
		addDetermine<SecondType, BaseTypes...>(function);
	}
	
	template<typename Type>
	void addDetermine(const detail::SimpleDetermineTypeFunc &) {}
	
	template<typename Type, typename BaseType, typename... BaseTypes>
	void addDetermine(const detail::SimpleDetermineTypeFunc &function) {
		YamlBuilder<BaseType>::template addDetermine<Type>(function);
		addDetermine<Type, BaseTypes...>(function);
	}
	
	template<typename Type, typename... Base>
	std::enable_if_t<!std::is_abstract_v<Type>, void>
	inherit(const std::vector<std::string> &aliases) {
		addBase<Type, Base...>(aliases);
		addBaseSub<Type, Base...>();
	}
	
	template<typename Type, typename... Base>
	std::enable_if_t<std::is_abstract_v<Type>, void> inherit() {
		addBaseSub<Type, Base...>();
	}
}