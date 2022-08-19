#pragma once
#include "../yaml.hpp"

namespace ui {
	template<typename T>
	class FileBuffer {
	protected:
		static std::map<std::string, T> objects;
		static std::map<std::string, T*> aliases;
		
	public:
		FileBuffer() = default;
		
		static T &getObjectReference(const std::string& name) {
			if(aliases.find(name) != aliases.end()) {
				return *aliases[name];
			}
			if(objects.find(name) == objects.end()) {
				objects[name].loadFromFile(name);
			}
			return objects[name];
		}
		
		static void setObject(const std::string &name, const std::string &filename) {
			objects[name].loadFromFile(filename);
		}
		
		static void addAlias(const std::string& name, const std::string& alias) {
			aliases[alias] = &getObjectReference(name);
		}
	};
	
	template<typename T>
	std::map<std::string, T> FileBuffer<T>::objects = {};
	
	template<typename T>
	std::map<std::string, T*> FileBuffer<T>::aliases = {};
}

void operator >>(const YAML::Node& node, sf::Texture*& texture);

void operator >>(const YAML::Node& node, sf::Font*& font);

namespace ui {
	typedef sf::Uint32 Uint32;
	
	struct SymbolPosition {
		ullint line;
		ullint number;
	};
	
	SymbolPosition readCharacterIndex(const YAML::Node &node, std::basic_ifstream<char32_t> &fin);
	
	std::basic_string<Uint32> char32_tStringToUint32String(std::basic_string<char32_t> str);
}

void operator >>(const YAML::Node& node, std::basic_string<char32_t>& string32);

void operator >>(const YAML::Node& node, sf::String& sfString);
