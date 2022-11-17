#pragma once
#include "../yamlBuilder.hpp"

namespace ui {
	template<typename Base, typename Type>
	void addType(std::vector<std::string> aliases = {});
	
	template<typename Type>
	void addBase(const std::vector<std::string>& aliases = {});
	
	template<typename Type, typename BaseType, typename... BaseTypes>
	void addBase(const std::vector<std::string>& aliases = {});
	
	template<typename Base, typename Type>
	void addSubtype();
	
	template<typename Subtype>
	void addBaseSub();
	
	template<typename Subtype, typename BaseType, typename... BaseTypes>
	void addBaseSub();
	
	template<typename Type>
	void addDetermine(const detail::DetermineTypeFunc &function);
	
	template<typename FirstType, typename SecondType, typename... BaseTypes>
	void addDetermine(const detail::DetermineTypeFunc &function);
	
	template<typename Type>
	void addDetermine(const detail::SimpleDetermineTypeFunc &);
	
	template<typename Type, typename BaseType, typename... BaseTypes>
	void addDetermine(const detail::SimpleDetermineTypeFunc &function = determine<Type>);
	
	template<typename Type, typename... Base>
	std::enable_if_t<!std::is_abstract_v<Type>, void>
	inherit(const std::vector<std::string> &aliases = {});
	
	template<typename Type, typename... Base>
	std::enable_if_t<std::is_abstract_v<Type>, void> inherit();
}

#include "shortcut.inl"