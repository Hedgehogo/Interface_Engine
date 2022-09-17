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
		
		static T &get(const std::string& name);
		
		static void setObject(const std::string &name, const std::string &filePath);
		
		static void addAlias(const std::string& name, const std::string& alias);
	};
}

#include "fileBuffer.inl"

void operator >>(const YAML::Node& node, sf::Texture*& texture);

void operator >>(const YAML::Node& node, sf::Font*& font);

namespace ui {
	typedef sf::Uint32 Uint32;
	
	struct SymbolPosition {
		ullint line;
		ullint number;
	};
	
	SymbolPosition readCharacterIndex(const YAML::Node &node, std::basic_ifstream<char32_t> &fin);
	
	std::basic_string<Uint32> u32stringToUint32String(std::basic_string<char32_t> str);
}

void operator >>(const YAML::Node& node, std::basic_string<char32_t>& string32);

void operator >>(const YAML::Node& node, sf::String& sfString);
