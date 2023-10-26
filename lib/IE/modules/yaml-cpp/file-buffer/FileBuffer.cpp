#include "FileBuffer.hpp"

#include <fstream>
#include <localisation/system.hpp>
#include "config.h"

#ifdef IE_ImageMagick_FOUND
#define MAGICKCORE_QUANTUM_DEPTH 16
#define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H
#include <Magick++.h>
#endif

namespace ie {
	SymbolPosition read_character_index(const YAML::Node& node, std::basic_ifstream<char32_t>& fin) {
		size_t line{0};
		size_t number{0};
		std::basic_string<char32_t> str;
		
		if(node.IsScalar()) {
			try {
				number = node.as<int>();
			} catch(YAML::BadConversion& e) {
				std::string keyword{node.as<std::string>()};
				if(keyword == "end") {
					std::getline(fin, str, U'\0');
					number = str.size() - 1;
					fin.seekg(0);
				} else if(keyword != "begin") {
					throw YAML::BadConversion(node.Mark());
				}
			}
		} else {
			if(node["symbol"]) {
				SymbolPosition position{read_character_index(node["symbol"], fin)};
				line = position.line;
				number = position.number;
				if(node["line-offset"])
					line += node["line-offset"].as<int>();
				if(node["offset"])
					number += node["offset"].as<int>();
			} else {
				if(node["line"])
					node["line"] >> line;
				if(node["line-offset"])
					line += node["line-offset"].as<int>();
				for(size_t i = 0; i < line; ++i) {
					std::getline(fin, str, U'\n');
				}
				if(node["number"]) {
					try {
						node["number"] >> number;
						if(node["offset"])
							number += node["offset"].as<int>();
					} catch(YAML::BadConversion& e) {
						std::string keyword{node["number"].as<std::string>()};
						if(keyword == "end") {
							std::getline(fin, str, U'\n');
							number = str.size() - 1;
							fin.clear();
							fin.seekg(0);
							return SymbolPosition{line, number};
						} else if(keyword != "begin") {
							throw YAML::BadConversion(node.Mark());
						}
					}
				}
			}
		}
		
		std::getline(fin, str, U'\n');
		if(str[0] == 65279)
			++number;
		while(number > str.size()) {
			number -= str.size() + 1;
			++line;
			std::getline(fin, str, U'\n');
		}
		
		fin.clear();
		fin.seekg(0);
		return SymbolPosition{line, number};
	}
	
	std::basic_string<Uint32> u32_string_to_uint32_string(std::basic_string<char32_t> str) {
		if(!str.empty()) {
			bool bom{str[0] == 65279}; //In the code it is used as value 0 or 1
			std::basic_string<Uint32> result(str.size() - bom, L' ');
			for(std::basic_string<char32_t>::size_type i = 0; i < str.size(); ++i) {
				result[i] = str[i + bom];
			}
			return result;
		}
		return std::basic_string<Uint32>{};
	}
	
	bool Decode<std::basic_string<char32_t>>::decode(const YAML::Node& node, std::basic_string<char32_t>& string32) {
		if(node.IsScalar()) {
			std::string str = node.as<std::string>();
			string32.resize(str.size());
			for(size_t i = 0; i < str.size(); ++i) {
				string32[i] = str[i];
			}
		} else {
			if(node["key"]) {
				if(node["directory"])
					loc::system.load_from_directory(node["directory"].as<std::string>());
				if(node["default-language"])
					loc::system.set_default_language(node["default-language"].as<std::string>());
				if(node["language"])
					loc::system.set_now_language(node["language"].as<std::string>());
				string32 = loc::system.get_text(node["key"].as<std::string>());
			} else {
				std::string file_path;
				node["file_path"] >> file_path;
				std::basic_ifstream<char32_t> fin(file_path);
				std::basic_string<char32_t> str{};
				if(node["line"]) {
					size_t line{node["line"].as<size_t>() + 1};
					for(size_t i = 0; i < line; ++i)
						std::getline(fin, str, U'\n');
				} else if(node["first-symbol"]) {
					SymbolPosition start{read_character_index(node["first-symbol"], fin)};
					if(node["last-symbol"]) {
						const YAML::Node& second_node = node["last-symbol"];
						SymbolPosition end{read_character_index(second_node, fin)};
						std::basic_string<char32_t> line;
						for(size_t i = 0; i < start.line; ++i)
							std::getline(fin, line, U'\n');
						for(size_t i = 0; i < end.line - start.line; ++i) {
							std::getline(fin, line, U'\n');
							str += line + U"\n";
						}
						std::getline(fin, line, U'\n');
						str += line.substr(0, end.number + 1);
					} else {
						for(size_t i = 0; i < start.line; ++i)
							std::getline(fin, str, U'\n');
						std::getline(fin, str, U'\0');
					}
					str = str.substr(start.number + (str[0] == 65279));
				} else {
					std::getline(fin, str, U'\0');
				}
				string32 = str;
			}
		}
		return true;
	}
	
	bool Decode<sf::String>::decode(const YAML::Node& node, sf::String& sf_string) {
		if(node.IsScalar()) {
			sf_string = sf::String(node.as<std::string>());
		} else {
			std::basic_string<char32_t> str;
			node >> str;
			sf_string = {u32_string_to_uint32_string(str)};
		}
		return true;
	}
	
	bool Decode<sf::Texture*>::decode(const YAML::Node& node, sf::Texture*& texture) {
		texture = &FileBuffer<sf::Texture>::get(node.as<std::string>());
		return true;
	}
	
	bool Decode<sf::Font*>::decode(const YAML::Node& node, sf::Font*& font) {
		font = &FileBuffer<sf::Font>::get(node.as<std::string>());
		return true;
	}
	
#ifdef IE_ImageMagick_FOUND
	void LoadFromFile<std::vector<sf::Texture>>::load(std::vector<sf::Texture>& object, std::string name) {
		std::list<Magick::Image> images;
		Magick::read_images(&images, name);
		
		object.resize(images.size());
		
		sf::Vector2<size_t> size_video{images.begin()->base_columns(), images.begin()->base_rows()};
		
		size_t i = 0;
		for(auto& frame: images) {
			frame.magick("RGBA");
			frame.background_color(Magick::Color("transparent"));
			frame.extent({static_cast<size_t>(size_video.x), static_cast<size_t>(size_video.y)}, Magick::CenterGravity);
			
			sf::Image sf_image;
			sf_image.create(size_video.x, size_video.y);
			for(size_t x = 0; x < size_video.x; ++x) {
				for(size_t y = 0; y < size_video.y; ++y) {
					Magick::Color pixel = frame.pixel_color(x, y);
					sf_image.set_pixel(x, y, {
										 static_cast<sf::Uint8>(QuantumScale * pixel.quantum_red() * 255),
										 static_cast<sf::Uint8>(QuantumScale * pixel.quantum_green() * 255),
										 static_cast<sf::Uint8>(QuantumScale * pixel.quantum_blue() * 255),
										 static_cast<sf::Uint8>(QuantumScale * pixel.quantum_alpha() * 255),
									 }
					);
				}
			}
			object[i].load_from_image(sf_image);
			++i;
		}
		
	}
	
	bool Decode<std::vector<sf::Texture>*>::decode(const YAML::Node& node, std::vector<sf::Texture>*& video) {
		video = &FileBuffer<std::vector<sf::Texture>>::get(node.as<std::string>());
		return true;
	}
#endif
}