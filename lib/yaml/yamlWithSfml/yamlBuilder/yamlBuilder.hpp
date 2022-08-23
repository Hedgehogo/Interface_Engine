#pragma once

#include <functional>
#include "../yaml.hpp"
#include "exceptions/yamlBuildExceptions.hpp"
#define UI_GET_TYPE_NAME(TYPE) (#TYPE)

namespace ui {
    const sf::Color nullColor{255, 255, 255, 0};

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
	T* loadFromYaml(std::string filename);
}

template<typename T>
std::void_t<decltype(T::createFromYaml(std::declval<YAML::Node>()))>
operator>>(const YAML::Node &node, T*& object);

#include "yamlBuilder.inl"
