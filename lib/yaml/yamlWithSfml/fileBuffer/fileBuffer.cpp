#include "fileBuffer.hpp"
#include <fstream>
#include <iostream>

void operator>>(const YAML::Node &node, sf::Texture *&texture) {
	texture = &ui::FileBuffer<sf::Texture>::getObjectReference(node.as<std::string>());
}

void operator>>(const YAML::Node &node, sf::Font *&font) {
	font = &ui::FileBuffer<sf::Font>::getObjectReference(node.as<std::string>());
}

namespace ui {
	SymbolPosition readCharacterIndex(const YAML::Node &node, std::basic_ifstream<char32_t> &fin) {
		ullint line{0};
		ullint number{0};
		std::basic_string<char32_t> str;
		
		if(node.IsScalar()) {
			try {
				number = node.as<llint>();
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
				SymbolPosition position{readCharacterIndex(node["symbol"], fin)};
				line = position.line;
				number = position.number;
				if(node["line-offset"])
					line += node["line-offset"].as<llint>();
				if(node["offset"])
					number += node["offset"].as<llint>();
			} else {
				if(node["line"])
					node["line"] >> line;
				if(node["line-offset"])
					line += node["line-offset"].as<llint>();
				for(ullint i = 0; i < line; ++i) {
					std::getline(fin, str, U'\n');
				}
				if(node["number"]) {
					try {
						node["number"] >> number;
						if(node["offset"])
							number += node["offset"].as<llint>();
					} catch(YAML::BadConversion &e) {
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
		if(str[0] == 65279) ++number;
		while(number > str.size()) {
			number -= str.size() + 1;
			++line;
			std::getline(fin, str, U'\n');
		}
		
		fin.clear();
		fin.seekg(0);
		return SymbolPosition{line, number};
	}
	
	std::basic_string<Uint32> char32_tStringToUint32String(std::basic_string<char32_t> str) {
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
}

void operator>>(const YAML::Node &node, std::basic_string<char32_t>& string32) {
    if (node.IsScalar()) {
        std::string str = node.as<std::string>();
        string32.resize(str.size());
        for (int i = 0; i < str.size(); ++i) {
            string32[i] = str[i];
        }
    } else {
        std::string filePath;
        node["file-path"] >> filePath;
        std::basic_ifstream<char32_t> fin(filePath);
        std::basic_string<char32_t> str{};
        if (node["line"]) {
            ullint line{node["line"].as<ullint>() + 1};
            for (ullint i = 0; i < line; ++i)
                std::getline(fin, str, U'\n');
        } else if (node["first-symbol"]) {
            ui::SymbolPosition start{ui::readCharacterIndex(node["first-symbol"], fin)};
            if (node["last-symbol"]) {
                const YAML::Node &secondNode = node["last-symbol"];
                ui::SymbolPosition end{ui::readCharacterIndex(secondNode, fin)};
                std::basic_string<char32_t> line;
                for (ullint i = 0; i < start.line; ++i)
                    std::getline(fin, line, U'\n');
                for (ullint i = 0; i < end.line - start.line; ++i) {
                    std::getline(fin, line, U'\n');
                    str += line + U"\n";
                }
                std::getline(fin, line, U'\n');
                str += line.substr(0, end.number + 1);
            } else {
                for (ullint i = 0; i < start.line; ++i)
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

void operator>>(const YAML::Node &node, sf::String &sfString) {
	if(node.IsScalar()) {
		sfString = sf::String(node.as<std::string>());
	} else {
		std::basic_string<char32_t> str;
		node >> str;
		sfString = {ui::char32_tStringToUint32String(str)};
	}
}
