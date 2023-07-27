#pragma once

#include "../yaml.hpp"

namespace ui {
	template<typename T>
	struct LoadFromFile {
		static void load(T& object, std::string name);
	};
	
	template<typename T>
	class FileBuffer {
	public:
		FileBuffer() = default;
		
		static T& get(const std::string& name);
		
		static void setObject(const std::string& name, const std::string& filePath);
		
		static void addAlias(const std::string& name, const std::string& alias);
	
	protected:
		static std::map<std::string, T> objects;
		static std::map<std::string, T*> aliases;
	};
	
	using Uint32 = sf::Uint32;
	
	struct SymbolPosition {
		std::size_t line;
		std::size_t number;
	};
	
	SymbolPosition readCharacterIndex(const YAML::Node& node, std::basic_ifstream<char32_t>& fin);
	
	std::basic_string<Uint32> u32stringToUint32String(std::basic_string<char32_t> str);
	
	template<>
	struct Decode<std::basic_string<char32_t>> {
		static bool decode(const YAML::Node& node, std::basic_string<char32_t>& string32);
	};
	
	template<>
	struct Decode<sf::String> {
		static bool decode(const YAML::Node& node, sf::String& sfString);
	};
	
	template<>
	struct Decode<sf::Texture*> {
		static bool decode(const YAML::Node& node, sf::Texture*& texture);
	};
	
	template<>
	struct Decode<sf::Font*> {
		static bool decode(const YAML::Node& node, sf::Font*& font);
	};
	
#ifdef IE_ImageMagick_FOUND
	template<>
	struct LoadFromFile<std::vector<sf::Texture>> {
		static void load(std::vector<sf::Texture>& object, std::string name);
	};
	
	template<>
	struct Decode<std::vector<sf::Texture>*> {
		static bool decode(const YAML::Node& node, std::vector<sf::Texture>*& video);
	};
#endif
}

#include "fileBuffer.inl"
