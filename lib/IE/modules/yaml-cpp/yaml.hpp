#pragma once

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <functional>
#include <box-ptr/BoxPtr.hpp>
#include <optional>
#include <option_result/option_result.hpp>

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

namespace ie {
	using namespace bp;
	
	auto demangle(const char* name) -> std::string;
	
	template<class T>
	auto type_name(const T& type) -> std::string;
	
	template<class T>
	auto type_name() -> std::string;
	
	auto type_name(const std::type_info& type_info) -> std::string;
	
	template<typename T>
	struct SetTypeName {
		static auto get() -> std::string {
			return type_name<T>();
		}
	};
	
	namespace detail {
		template<typename T>
		auto get_template_name() -> std::string {
			std::string name = type_name<T>();
			name.resize(name.find('<'));
			return name;
		}
	}
	
	template<template<typename...> typename Type, typename... Types>
	struct SetTypeName<Type<Types...> > {
		static auto get() -> std::string {
			return detail::get_template_name<Type<Types...> >();
		}
	};
	
	template<>
	struct SetTypeName<std::string> {
		static auto get() -> std::string {
			return "String";
		}
	};
	
	template<typename T, typename E>
	using type = T;
	
	namespace detail {
		template<typename T>
		struct GetTypeName {
			static auto get() -> std::string {
				return SetTypeName<T>::get();
			}
		};
		
		template<typename... Ts>
		struct GetTypeNames {
			static auto get() -> std::string {
				return {};
			}
		};
		
		template<typename T>
		struct GetTypeNames<T> {
			static auto get() -> std::string {
				return GetTypeName<T>::get();
			}
		};
		
		template<typename F, typename... Types>
		struct GetTypeNames<F, Types...> {
			static auto get() -> std::string {
				return GetTypeName<F>::get() + ", " + GetTypeNames<Types...>::get();
			}
		};
		
		template<template<typename...> typename Type, typename... Types>
		struct GetTypeName<Type<Types...> > {
			static auto get() -> std::string {
				return SetTypeName<Type<Types...> >::get() + "<" + GetTypeNames<Types...>::get() + ">";
			}
		};
	}
	
	template<typename T>
	auto get_type_name() -> std::string {
		return detail::GetTypeName<T>::get();
	}
	
	template<typename T>
	struct Decode;
	
	template<typename T>
	struct Decode<T*> {
		static auto decode(const YAML::Node& node, T*& object) -> std::enable_if_t<std::is_class_v<T>, bool>;
	};
	
	template<typename T>
	struct DecodePointer {
	};
	
	template<typename T>
	struct Encode;
	
	template<typename T>
	auto convert(const T& rhs) -> YAML::Node;
	
	
	template<typename T>
	auto create_pointer(const YAML::Node& node, T*& object) -> bool;
	
	
	template<typename T>
	auto convert(const T*& rhs) -> std::enable_if_t<std::is_class_v<T>, YAML::Node>;
	
	template<typename T>
	auto convert(const YAML::Node& node, T*& object) -> std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>;
	
	template<typename T>
	auto convert(const YAML::Node& node, T*& object) -> std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>;
	
	auto convert_bool(const YAML::Node& node, std::string true_value, std::string false_value) -> bool;
	
	template<typename T>
	auto convert_default(const YAML::Node& node, const T& default_value) -> T;
	
	template<typename T>
	auto conv_def(const YAML::Node& node, const T& default_value) -> T;
	
	template<typename B, typename T, typename ...Arg>
	auto convert_default_ptr(const YAML::Node& node, Arg&& ... arg) -> B*;
	
	template<typename B, typename T, typename ...Arg>
	auto conv_def_ptr(const YAML::Node& node, Arg&& ... arg) -> B*;
	
	template<typename B, typename T, typename ...Arg>
	auto convert_default_box_ptr(const YAML::Node& node, Arg&& ... arg) -> BoxPtr<B>;
	
	template<typename B, typename T, typename ...Arg>
	auto conv_def_box_ptr(const YAML::Node& node, Arg&& ... arg) -> BoxPtr<B>;
	
	auto convert_bool_default(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value = false) -> bool;
	
	auto conv_bool_def(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value = false) -> bool;
	
	
	template<typename T>
	struct Decode<BoxPtr<T> > {
		static auto decode(const YAML::Node& node, BoxPtr<T>& object) -> std::enable_if_t<std::is_class_v<T>, bool>;
	};
	
	/*old_yaml_decode
	template<typename T>
	struct Decode<orl::Option<T> > {
		static bool decode(const YAML::Node& node, orl::Option<T>& object);
	};
	*/
	
	/*old_yaml_decode
	template<typename T>
	struct Decode<std::vector<T> > {
		static bool decode(const YAML::Node& node, std::vector<T>& vector);
	};
	*/
	
	
	/*old_yaml_decode
	template<typename T>
	struct Decode<sf::Vector2<T> > {
		static bool decode(const YAML::Node& node, sf::Vector2<T>& vector);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Vector2<float> > {
		static bool decode(const YAML::Node& node, sf::Vector2<float>& vector);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Vector2<int> > {
		static bool decode(const YAML::Node& node, sf::Vector2<int>& vector);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Vector2<size_t> > {
		static bool decode(const YAML::Node& node, sf::Vector2<size_t>& vector);
	};
	*/
	
	
	/*old_yaml_decode
	template<typename T>
	struct Decode<sf::Rect<T> > {
		static bool decode(const YAML::Node& node, sf::Rect<T>& rect);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Color> {
		static bool decode(const YAML::Node& node, sf::Color& color);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Text::Style> {
		static bool decode(const YAML::Node& node, sf::Text::Style& style);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Mouse::Button> {
		static bool decode(const YAML::Node& node, sf::Mouse::Button& button);
	};
	*/
	
	
	/*old_yaml_decode
	template<>
	struct Decode<sf::Shader> {
		static bool decode(const YAML::Node& node, sf::Shader& shader);
	};
	*/
	
	template<typename T>
	auto get_s_value(const YAML::Node& node, bool create_if_not_exist = true) -> std::shared_ptr<T>;
}

namespace YAML {
	template<typename T>
	struct convert {
		static auto encode(const T& rhs) -> Node;
		
		static auto decode(const Node& node, T& rhs) -> bool;
	};
}

template<typename T>
auto operator>>(const YAML::Node& node, T& value) -> std::enable_if_t<std::is_copy_constructible_v<T>, void>;

template<typename T>
auto operator>>(const YAML::Node& node, T& value) -> std::enable_if_t<!std::is_copy_constructible_v<T>, void>;

#include "yaml.inl"
