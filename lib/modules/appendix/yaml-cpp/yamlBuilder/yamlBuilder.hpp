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
	T* loadFromYamlFile(const YAML::Node &node, bool &correctly);
	
	template<typename T>
	T* loadFromYamlIf(const YAML::Node &node, bool &correctly);

	template<typename T>
	T* loadFromYamlObject(const YAML::Node &node, bool &correctly);
	
	template<typename T>
	class YamlBuilder {
	public:
		typedef std::function<T*(const YAML::Node& node, bool &correctly)> MakeObject;
		typedef std::function<T*(const YAML::Node& node, std::string type, bool &correctly)> MakeSubobject;
		typedef std::function<std::string(std::string typeName)> TypeNameDeformer;
		
	protected:
		static std::map<std::string, MakeObject> typeMap;
		static std::vector<MakeSubobject> subtypeMap;
		static TypeNameDeformer typeNameDeform;
		
	public:
		YamlBuilder() = default;
		
		static void setTypeNameDeformer(TypeNameDeformer typeNameDeform);
		
		static void add(MakeObject function, std::string type, std::vector<std::string> aliases = {});
		
		static void addSubtype(MakeSubobject function);
		
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
		
		static T* build(const YAML::Node& node, std::string type, bool &correctly);
	};
	
	template<typename T>
	T* loadFromYaml(std::string filePath);
}

#include "yamlBuilder.inl"
