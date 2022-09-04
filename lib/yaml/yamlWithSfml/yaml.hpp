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

std::string demangle(const char* name);

template <class T>
std::string type_name(const T& type);

template <class T>
std::string type_name();

template<typename T>
std::void_t<decltype(T::createFromYaml(std::declval<YAML::Node>()))>
operator>>(const YAML::Node &node, T*& object);

template<typename T>
void operator >>(const YAML::Node& node, T& value);

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second);

template<typename T>
void operator >>(const YAML::Node& node, std::vector<T>& vector);

void operator >>(const YAML::Node& node, sf::Vector2<float>& vector);

void operator >>(const YAML::Node& node, sf::Vector2<int>& vector);

void operator >>(const YAML::Node& node, sf::Vector2<uint>& vector);

template <typename T>
void operator>>(const YAML::Node &node, sf::Rect<T> &rect);

void operator >>(const YAML::Node& node, sf::Color& color);

void operator >>(const YAML::Node& node, sf::Text::Style& style);

void operator >>(const YAML::Node& node, sf::Mouse::Button& button);

void operator >>(const YAML::Node& node, sf::Shader& shader);

bool createBoolFromYaml(const YAML::Node& node, std::string trueValue, std::string falseValue);

#include "yaml.inl"
