#pragma once

#include "../yaml.hpp"

namespace ui {
	template<typename T>
	struct LoadFromFile {
		static void load(T& object, std::string name);
	};
	
	template<typename T>
	class FileBuffer {
	protected:
		static std::map<std::string, T> objects;
		static std::map<std::string, T*> aliases;
	
	public:
		FileBuffer() = default;
		
		static T& get(const std::string& name);
		
		static void setObject(const std::string& name, const std::string& filePath);
		
		static void addAlias(const std::string& name, const std::string& alias);
	};
	
	using Uint32 = sf::Uint32;
	
	struct SymbolPosition {
		ullint line;
		ullint number;
	};
	
	SymbolPosition readCharacterIndex(const YAML::Node& node, std::basic_ifstream<char32_t>& fin);
	
	std::basic_string<Uint32> u32stringToUint32String(std::basic_string<char32_t> str);
	
	template<>
	bool convert(const YAML::Node& node, std::basic_string<char32_t>& string32);
	
	template<>
	struct Decode<std::basic_string<char32_t>> {
		static bool decode(const YAML::Node& node, std::basic_string<char32_t>& string32);
	};
	
	template<>
	bool convert(const YAML::Node& node, sf::String& sfString);
	
	template<>
	struct Decode<sf::String> {
		static bool decode(const YAML::Node& node, sf::String& sfString);
	};
	
	template<>
	bool convert<sf::Texture>(const YAML::Node &node, sf::Texture *&texture);
	
	template<>
	struct Decode<sf::Texture*> {
		static bool decode(const YAML::Node &node, sf::Texture*& texture);
	};
	
	template<>
	bool convert<sf::Font>(const YAML::Node &node, sf::Font *&font);
	
	template<>
	struct Decode<sf::Font*> {
		static bool decode(const YAML::Node &node, sf::Font*& font);
	};
	
	template<>
	struct LoadFromFile<std::vector<sf::Texture>> {
		static void load(std::vector<sf::Texture>& object, std::string name);
	};
	
	template<>
	bool convert<std::vector<sf::Texture>>(const YAML::Node &node, std::vector<sf::Texture> *&video);
	
	template<>
	struct Decode<std::vector<sf::Texture>*> {
		static bool decode(const YAML::Node &node, std::vector<sf::Texture>*& video);
	};
	
}

#include "fileBuffer.inl"
