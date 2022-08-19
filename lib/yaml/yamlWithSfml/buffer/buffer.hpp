#pragma once
#include "../yaml.hpp"

namespace ui {
	template<typename T>
	class Buffer {
	public:
		typedef std::function<T*(const YAML::Node &node)> makeSubobject;
		
	protected:
		static std::map<std::string, T> objects;
	
	public:
		Buffer() = default;
		
		static bool existObject(const std::string& name) {
			return objects.find(name) != objects.end();
		}
		
		static void addObject(const YAML::Node &node) {
			std::string name;
			node["name"] >> name;
			if(!existObject(name)) {
				node >> objects[name];
			} else {
				throw YAML::BadConversion{node.Mark()};
			}
		}
		
		static T &getObjectReference(const std::string& name) {
			return objects.at(name);
		}
		
		static T &getObjectReference(const YAML::Node &node) {
			std::string name;
			if(node.IsScalar()) {
				node >> name;
			} else {
				node["name"] >> name;
				if(!existObject(name)) {
					node >> objects[name];
				}
			}
			return objects[name];
		}
	};
	
	template<typename T>
	std::map<std::string, T> Buffer<T>::objects = {};
}
