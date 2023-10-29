#pragma once

#include "../yaml-builder.hpp"

namespace ie {
	template<typename Base, typename Type>
	void inherit(const std::vector<std::string>& aliases = {});
	
	template<typename Base>
	constexpr void add_type() noexcept {
	}
	
	template<typename Base, typename Type, typename... Types>
	void add_type();
	
	template<typename Base, typename... Types>
	void add_type(const std::vector<std::string>& aliases);
	
	template<typename Type>
	constexpr void add_base() noexcept {
	}
	
	template<typename Type, typename Base, typename... Bases>
	void add_base();
	
	template<typename Type, typename... Bases>
	void add_base(const std::vector<std::string>& aliases);
	
	template<typename Type>
	void add_aliases(const std::vector<std::string>& aliases);
	
	template<typename Type>
	void add_determine(const detail::DetermineTypeFunc& function);
	
	template<typename Type>
	void add_determine(const detail::SimpleDetermineTypeFunc& function = determine<Type>);
	
	template<typename Base>
	void add_func(typename detail::FuncYamlBuilder::BuildFunc<Base> function, std::vector<std::string> names = {});
}

#include "shortcut.inl"