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
	
	std::string demangle(const char* name);
	
	template<class T>
	std::string type_name(const T& type);
	
	template<class T>
	std::string type_name();
	
	std::string type_name(const std::type_info& type_info);
	
	template<typename T>
	struct SetTypeName {
		static std::string get() {
			return type_name<T>();
		}
	};
	
	namespace detail {
		template<typename T>
		std::string get_template_name() {
			std::string name = type_name<T>();
			name.resize(name.find('<'));
			return name;
		}
	}
	
	template<template<typename...> typename Type, typename... Types>
	struct SetTypeName<Type<Types...> > {
		static std::string get() {
			return detail::get_template_name<Type<Types...> >();
		}
	};
	
	template<>
	struct SetTypeName<std::string> {
		static std::string get() {
			return "String";
		}
	};
	
	template<typename T, typename E>
	using type = T;
	
	namespace detail {
		template<typename T>
		struct GetTypeName {
			static std::string get() {
				return SetTypeName<T>::get();
			}
		};
		
		template<typename... Ts>
		struct GetTypeNames {
			static std::string get() {
				return {};
			}
		};
		
		template<typename T>
		struct GetTypeNames<T> {
			static std::string get() {
				return GetTypeName<T>::get();
			}
		};
		
		template<typename F, typename... Types>
		struct GetTypeNames<F, Types...> {
			static std::string get() {
				return GetTypeName<F>::get() + ", " + GetTypeNames<Types...>::get();
			}
		};
		
		template<template<typename...> typename Type, typename... Types>
		struct GetTypeName<Type<Types...> > {
			static std::string get() {
				return SetTypeName<Type<Types...> >::get() + "<" + GetTypeNames<Types...>::get() + ">";
			}
		};
	}
	
	template<typename T>
	std::string get_type_name() {
		return detail::GetTypeName<T>::get();
	}
	
	template<typename T>
	struct Decode;
	
	template<typename T>
	struct Decode<T*> {
		static std::enable_if_t<std::is_class_v<T>, bool>
		decode(const YAML::Node& node, T*& object);
	};
	
	template<typename T>
	struct DecodePointer {
	};
	
	template<typename T>
	struct Encode;
	
	template<typename T>
	YAML::Node convert(const T& rhs);
	
	
	template<typename T>
	bool create_pointer(const YAML::Node& node, T*& object);
	
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, YAML::Node>
	convert(const T*& rhs);
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object);
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object);
	
	bool convert_bool(const YAML::Node& node, std::string true_value, std::string false_value);
	
	template<typename T>
	T convert_default(const YAML::Node& node, const T& default_value);
	
	template<typename T>
	T conv_def(const YAML::Node& node, const T& default_value);
	
	template<typename B, typename T, typename ...Arg>
	B* convert_default_ptr(const YAML::Node& node, Arg&& ... arg);
	
	template<typename B, typename T, typename ...Arg>
	B* conv_def_ptr(const YAML::Node& node, Arg&& ... arg);
	
	template<typename B, typename T, typename ...Arg>
	BoxPtr<B> convert_default_box_ptr(const YAML::Node& node, Arg&& ... arg);
	
	template<typename B, typename T, typename ...Arg>
	BoxPtr<B> conv_def_box_ptr(const YAML::Node& node, Arg&& ... arg);
	
	bool convert_bool_default(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value = false);
	
	bool conv_bool_def(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value = false);
	
	
	template<typename T>
	struct Decode<BoxPtr<T> > {
		static std::enable_if_t<std::is_class_v<T>, bool>
		decode(const YAML::Node& node, BoxPtr<T>& object);
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
	std::shared_ptr<T> get_s_value(const YAML::Node& node, bool create_if_not_exist = true);
}

namespace YAML {
	template<typename T>
	struct convert {
		static Node encode(const T& rhs);
		
		static bool decode(const Node& node, T& rhs);
	};
}

template<typename T>
std::enable_if_t<std::is_copy_constructible_v<T>, void>
operator>>(const YAML::Node& node, T& value);

template<typename T>
std::enable_if_t<!std::is_copy_constructible_v<T>, void>
operator>>(const YAML::Node& node, T& value);

#include "yaml.inl"
