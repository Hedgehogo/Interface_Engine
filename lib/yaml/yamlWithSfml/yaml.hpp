#pragma once
#include <SFML/Graphics.hpp>
#if WIN32
#define YAML_CPP_STATIC_DEFINE
#endif
#include "yaml-cpp/yaml.h"

typedef long long llint;

typedef unsigned int uint;

typedef unsigned long long ullint;

template<typename T>
void operator >>(const YAML::Node& node, T& value) {
	value = node.as<T>();
}

template<typename T>
void operator >>(const YAML::Node& node, std::vector<T>& vector) {
	for(const auto &item : node) {
		vector.resize(vector.size() + 1);
		item >> vector[vector.size() - 1];
	}
}

template<typename T>
void operator >>(const YAML::Node& node, sf::Vector2<T>& vector) {
	vector.x = node[0].as<T>();
	vector.y = node[1].as<T>();
}

void operator >>(const YAML::Node& node, sf::Vector2<float>& vector);

void operator >>(const YAML::Node& node, sf::Vector2<int>& vector);

void operator >>(const YAML::Node& node, sf::Vector2<uint>& vector);

template <typename T>
void operator>>(const YAML::Node &node, sf::Rect<T> &rect) {
	sf::Vector2<T> position;
	sf::Vector2<T> size;
	node["position"] >> position;
	node["size"] >> size;
	rect = sf::Rect<T>{position, size};
}

void operator >>(const YAML::Node& node, sf::Color& color);

void operator >>(const YAML::Node& node, sf::Text::Style& style);

void operator >>(const YAML::Node& node, sf::Mouse::Button& button);

bool createBoolFromYaml(const YAML::Node& node, std::string trueValue, std::string falseValue);
