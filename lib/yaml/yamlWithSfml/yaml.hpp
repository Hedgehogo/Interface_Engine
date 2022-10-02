#pragma once
#include <string>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#if WIN32
#define YAML_CPP_STATIC_DEFINE
#endif
#include "yaml-cpp/yaml.h"

typedef long long llint;
typedef unsigned int uint;
typedef unsigned long long ullint;

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

namespace ui {
	std::string demangle(const char* name);
	
	template <class T>
	std::string type_name(const T& type);
	
	template <class T>
	std::string type_name();
	
	template<typename T, typename E>
	using type = T;
	
	template <typename T>
	T* pointerConvert(const YAML::Node& node) { return nullptr; }
	
	template <typename T>
	YAML::Node convert(const T &rhs);
	
	template <typename T>
	bool convert(const YAML::Node &node, T &object);
	
	
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T>, YAML::Node>
	convert(const T *&rhs);
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object);
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object);
	
	bool convertBool(const YAML::Node& node, std::string trueValue, std::string falseValue);
	
	template <typename T>
	T convertDefault(const YAML::Node &node, const T &defaultValue);
	
	template<typename T>
	T convDef(const YAML::Node &node, const T &defaultValue);
	
	template<typename T>
	bool convert(const YAML::Node &node, std::vector<T> &vector);
	
	template<typename T>
	bool convert(const YAML::Node& node, sf::Vector2<T>& vector);
	
	template<>
	bool convert(const YAML::Node &node, sf::Vector2<float> &vector);
	
	template<>
	bool convert(const YAML::Node &node, sf::Vector2<int> &vector);
	
	template<>
	bool convert(const YAML::Node &node, sf::Vector2<uint> &vector);
	
	template <typename T>
	bool convert(const YAML::Node &node, sf::Rect<T>  &rect);
	
	template<>
	bool convert(const YAML::Node &node, sf::Color &color);
	
	template<>
	bool convert(const YAML::Node &node, sf::Text::Style &style);
	
	template<>
	bool convert(const YAML::Node &node, sf::Mouse::Button &button);
	
	template<>
	bool convert(const YAML::Node &node, sf::Shader &shader);
}

namespace YAML {
	template <typename T>
	struct convert {
		static Node encode(const T& rhs);
		
		static bool decode(const Node& node, T& rhs);
	};
}

template<typename T>
std::enable_if_t<std::is_copy_constructible_v<T>, void>
operator >>(const YAML::Node& node, T& value);

template<typename T>
std::enable_if_t<!std::is_copy_constructible_v<T>, void>
operator >>(const YAML::Node& node, T& value);

#include "yaml.inl"
