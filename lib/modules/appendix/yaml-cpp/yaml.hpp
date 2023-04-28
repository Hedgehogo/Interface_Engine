#pragma once

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <functional>

typedef long long llint;
typedef unsigned int uint;
typedef unsigned long long ullint;

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

namespace ui {
	std::string demangle(const char* name);
	
	template<class T>
	std::string type_name(const T& type);
	
	template<class T>
	std::string type_name();
	
	template<typename T, typename E>
	using type = T;
	
	template<typename T>
	struct Decode;
	
	template<typename T>
	struct Decode<T*> {
		static std::enable_if_t<std::is_class_v<T>, bool>
		decode(const YAML::Node& node, T*& object);
	};
	
	template<typename T>
	struct DecodePointer;
	
	template<typename T>
	struct Encode;
	
	template<typename T>
	YAML::Node convert(const T& rhs);
	
	
	
	template<typename T>
	bool createPointer(const YAML::Node& node, T*& object);
	
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, YAML::Node>
	convert(const T*& rhs);
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object);
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object);
	
	bool convertBool(const YAML::Node& node, std::string trueValue, std::string falseValue);
	
	template<typename T>
	T convertDefault(const YAML::Node& node, const T& defaultValue);
	
	template<typename T>
	T convDef(const YAML::Node& node, const T& defaultValue);
	
	bool convertBoolDefault(const YAML::Node& node, std::string trueValue, std::string falseValue, bool defaultValue = false);
	
	bool convBoolDef(const YAML::Node& node, std::string trueValue, std::string falseValue, bool defaultValue = false);
	
	
	
	template<typename T>
	struct Decode<std::vector<T>> {
		static bool decode(const YAML::Node& node, std::vector<T>& vector);
	};
	
	
	
	template<typename T>
	struct Decode<sf::Vector2<T>> {
		static bool decode(const YAML::Node& node, sf::Vector2<T>& vector);
	};
	
	
	
	template<>
	struct Decode<sf::Vector2<float>> {
		static bool decode(const YAML::Node& node, sf::Vector2<float>& vector);
	};
	
	
	
	template<>
	struct Decode<sf::Vector2<int>> {
		static bool decode(const YAML::Node& node, sf::Vector2<int>& vector);
	};
	
	
	
	template<>
	struct Decode<sf::Vector2<uint>> {
		static bool decode(const YAML::Node& node, sf::Vector2<uint>& vector);
	};
	
	
	
	template<typename T>
	struct Decode<sf::Rect<T>> {
		static bool decode(const YAML::Node& node, sf::Rect<T>& rect);
	};
	
	
	
	template<>
	struct Decode<sf::Color> {
		static bool decode(const YAML::Node& node, sf::Color& color);
	};
	
	
	
	template<>
	struct Decode<sf::Text::Style> {
		static bool decode(const YAML::Node& node, sf::Text::Style& style);
	};
	
	
	
	template<>
	struct Decode<sf::Mouse::Button> {
		static bool decode(const YAML::Node& node, sf::Mouse::Button& button);
	};
	
	
	
	template<>
	struct Decode<sf::Shader> {
		static bool decode(const YAML::Node& node, sf::Shader& shader);
	};
	
	template<typename T>
	std::shared_ptr<T> getSValue(const YAML::Node& node, bool createIfNotExist = true);
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
