#pragma once
#include "../yamlBuilder.hpp"

namespace ui {
	template <typename Base, typename Type>
	void inherit(const std::vector<std::string> &aliases = {});
	
	template <typename Base>
	constexpr void addType() noexcept {}
	
	template <typename Base, typename Type, typename... Types>
	void addType();
	
	template <typename Base, typename... Types>
	void addType(const std::vector<std::string> &aliases);
	
	template <typename Type>
	constexpr void addBase() noexcept {}
	
	template <typename Type, typename Base, typename... Bases>
	void addBase();
	
	template <typename Type, typename... Bases>
	void addBase(const std::vector<std::string> &aliases);
	
	template <typename Type>
	void addAliases(const std::vector<std::string> &aliases);
	
	template <typename Type>
	void addDetermine(const detail::DetermineTypeFunc &function);
	
	template <typename Type>
	void addDetermine(const detail::SimpleDetermineTypeFunc &function = determine<Type>);
	
	template <typename Base>
	void addFunc(typename detail::FuncYamlBuilder::BuildFunc<Base> function, std::vector<std::string> names = {});
}

#include "shortcut.inl"