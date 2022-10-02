#pragma once

#include <functional>
#include "../yaml.hpp"
#include "../buffer/buffer.hpp"
#include "exceptions/yamlBuildExceptions.hpp"
#include <iostream>
#include <bitset>
#include "../objectBuffer/objectBuffer.hpp"

namespace ui {
    const sf::Color nullColor{255, 255, 255, 0};
	
	std::string removeNamespace(std::string typeName, std::string nameSpace);
	
	template<typename T>
	T* loadFromYamlFile(const YAML::Node &node);
	
	template<typename T>
	T* loadFromYamlIf(const YAML::Node &node);

	template<typename T>
	T* loadFromYamlObject(const YAML::Node &node);
	
	template<typename T>
	class YamlBuilder {
	public:
		typedef std::function<T*(const YAML::Node& node)> makeObject;
		typedef std::function<T*(const YAML::Node& node, std::string type)> makeSubobject;
		
	protected:
		static std::map<std::string, makeObject> typeMap;
		static std::vector<makeSubobject> subtypeMap;
		static std::string deleteNamespace;
		static std::string suffixType;
		
	public:
		YamlBuilder() = default;
		
		static void setDeleteNamespace(std::string deleteNamespace);
		
		static void setSuffixType(std::string suffixType);
		
		static void add(makeObject function, std::string type, std::vector<std::string> aliases = {});
		
		static void addSubtype(makeSubobject function);
		
		static void addAlias(std::string type, std::string alias);
		
		static void addAliases(std::string type, std::vector<std::string> aliases);
		
		template <typename Subtype>
		static void add(std::vector<std::string> aliases = {});
		
		template<typename Subtype>
		static void addSubtype();
		
		template <typename Subtype>
		static void addAlias(std::string alias);
		
		template <typename Subtype>
		static void addAliases(std::vector<std::string> aliases);
		
		static T* build(const YAML::Node& node, std::string type);
	};
	
	template<typename T>
	T* loadFromYaml(std::string filePath);
}

#include "yamlBuilder.inl"
