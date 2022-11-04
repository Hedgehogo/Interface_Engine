#pragma once

#include "../buffer/buffer.hpp"
#include "exception/yamlBuildExceptions.hpp"

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
	
	template<typename Base, typename Type>
	void addType(std::vector<std::string> aliases = {});
	
	template<typename Type>
	void addBase(const std::vector<std::string>& aliases = {});
	
	template<typename Type, typename BaseType, typename... BaseTypes>
	void addBase(const std::vector<std::string>& aliases = {});
	
	template<typename Base, typename Type>
	void addSubtype();
	
	template<typename Subtype>
	void addBaseSub();
	
	template<typename Subtype, typename BaseType, typename... BaseTypes>
	void addBaseSub();
	
	template<typename Type, typename... Base>
	std::enable_if_t<!std::is_abstract_v<Type>, void>
	inherit(const std::vector<std::string> &aliases = {});
	
	template<typename Type, typename... Base>
	std::enable_if_t<std::is_abstract_v<Type>, void> inherit();
	
	template<typename T>
	T* loadFromYaml(std::string filePath);
}

#include "yamlBuilder.inl"
