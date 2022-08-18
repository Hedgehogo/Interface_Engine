#pragma once

#include <functional>
#include "../yaml.hpp"
#include "exceptions/yamlBuildExceptions.hpp"
#define UI_GET_TYPE_NAME(TYPE) (#TYPE)

namespace ui {
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
		
		static void add(makeObject function, std::string type, std::vector<std::string> aliases = {}) {
			typeMap[type] = function;
			addAliases(type, aliases);
		}
		
		static void addSubtype(makeSubobject function) {
			subtypeMap.push_back(function);
		}
		
		static void addAlias(std::string type, std::string alias) {
			typeMap[alias] = typeMap.at(type);
		}
		
		static void addAliases(std::string type, std::vector<std::string> aliases) {
			for(const auto &alias: aliases) {
				addAlias(type, alias);
			}
		}
		
		template<typename C>
		static void add(std::vector<std::string> aliases = {}) {
			add(C::createFromYaml, UI_GET_TYPE_NAME(C), aliases);
		}
		
		template<typename C>
		static void addSubtype() {
			addSubtype(YamlBuilder<C>::build);
		}
		
		template<typename C>
		static void addAlias(std::string alias) {
			addAlias(UI_GET_TYPE_NAME(C), alias);
		}
		
		template<typename C>
		static void addAliases(std::vector<std::string> aliases) {
			addAliases(UI_GET_TYPE_NAME(C), aliases);
		}
		
		static T* build(const YAML::Node& node, std::string type) {
			for(const auto &subtype: subtypeMap) {
				try {
					return subtype(node, type);
				} catch (ui::NonexistentTypeYamlException&) {}
			}
			try {
				return typeMap.at(type)(node);
			} catch (std::out_of_range&) {
				throw ui::NonexistentTypeYamlException{type};
			}
		}
	};
	
	template<typename T>
	std::map<std::string, typename YamlBuilder<T>::makeObject> YamlBuilder<T>::typeMap = {};
	
	template<typename T>
	std::vector<typename YamlBuilder<T>::makeSubobject> YamlBuilder<T>::subtypeMap = {};
}

template<typename T>
std::void_t<decltype(T::createFromYaml(std::declval<YAML::Node>()))>
operator>>(const YAML::Node &node, T*& object) {
	if(node["type"]) {
		std::string type;
		node["type"] >> type;
		object = ui::YamlBuilder<T>::build(node, type);
	} else {
		T* result = dynamic_cast<T*>(T::createFromYaml(node));
		if(!result) throw ui::AbstractTypeYamlException{};
		object = result;
	}
}

namespace ui {
	template<typename T>
	T* loadFromYaml(std::string filename) {
		YAML::Node node = YAML::LoadFile(filename);
		T* object;
		node >> object;
		return object;
	}
}
