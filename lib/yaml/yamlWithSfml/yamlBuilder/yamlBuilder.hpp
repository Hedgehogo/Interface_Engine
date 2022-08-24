#pragma once

#include <functional>
#include "../yaml.hpp"
#include "../buffer/buffer.hpp"
#include "exceptions/yamlBuildExceptions.hpp"
#include <iostream>
#include <bitset>
#define UI_GET_TYPE_NAME(TYPE) (#TYPE)

namespace ui {
    const sf::Color nullColor{255, 255, 255, 0};
	
	template<typename T>
	T* loadFromYamlFile(const YAML::Node &node);
	
	template<typename T>
	T* loadFromYamlIf(const YAML::Node &node) {
		T* object;
		bool condition{Buffer::existObject(node["condition"])};
		std::cout << std::bitset<8>(condition) << " ";
		if(condition) {
			std::cout << "1 ";
			node["first"] >> object;
			std::cout << "1. ";
		} else {
			std::cout << "0 ";
			Buffer::addObject<WithValue<bool>>(node["condition"]);
			node["second"] >> object;
			std::cout << "0. ";
		}
		std::cout << "n" << "\n";
		return object;
	}

	template<typename T>
	class YamlBuilder {
	public:
		typedef std::function<T*(const YAML::Node& node)> makeObject;
		typedef std::function<T*(const YAML::Node& node, std::string type)> makeSubobject;
		
	protected:
		static std::map<std::string, makeObject> typeMap;
		static std::vector<makeSubobject> subtypeMap;
		
	public:
		YamlBuilder() = default;
		
		static void add(makeObject function, std::string type, std::vector<std::string> aliases = {});
		
		static void addSubtype(makeSubobject function);
		
		static void addAlias(std::string type, std::string alias);
		
		static void addAliases(std::string type, std::vector<std::string> aliases);
		
		template<typename Subtype>
		static void addSubtype();
		
		static T* build(const YAML::Node& node, std::string type);
	};
	
	template<typename T>
	T* loadFromYaml(std::string filePath);
}

#include "yamlBuilder.inl"
