#include "yaml.hpp"

#ifdef __GNUG__

#include <cstdlib>
#include <memory>
#include <utility>
#include <cxxabi.h>

namespace ie {
	std::string demangle(const char* name) {
		int status = -4; // some arbitrary value to eliminate the compiler warning
		
		// enable c++11 by passing the flag -std=c++11 to g++
		std::unique_ptr<char, void (*)(void*)> res{
			abi::__cxa_demangle(name, nullptr, nullptr, &status),
			std::free
		};
		
		return (status == 0) ? res.get() : name;
	}
}
#else
// does nothing if not g++
namespace ie {
	std::string demangle(const char* name) {
		return name;
	}
}
#endif

namespace ie {
	bool convert_bool(const YAML::Node& node, std::string true_value, std::string false_value) {
		std::string parameter{node.as<std::string>()};
		
		if(parameter == true_value)
			return true;
		else if(parameter == false_value)
			return false;
		else
			throw YAML::BadConversion{node.Mark()};
	}
	
	bool convert_bool_default(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value) {
		if(node.IsDefined()) {
			return convert_bool(node, std::move(true_value), std::move(false_value));
		} else {
			return default_value;
		}
	}
	
	bool conv_bool_def(const YAML::Node& node, std::string true_value, std::string false_value, bool default_value) {
		return convert_bool_default(node, std::move(true_value), std::move(false_value), default_value);
	}
	
	std::string type_name(const std::type_info& type_info) {
		return demangle(type_info.name());
	}
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Vector2<float>>::decode(const YAML::Node& node, sf::Vector2<float>& vector) {
		if(node.IsSequence()) {
			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();
		} else if(node.IsScalar()) {
			std::string str_vector = node.as<std::string>();
			sscanf(str_vector.c_str(), "%f,%f", &vector.x, &vector.y);
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Vector2<int>>::decode(const YAML::Node& node, sf::Vector2<int>& vector) {
		if(node.IsSequence()) {
			vector.x = node[0].as<int>();
			vector.y = node[1].as<int>();
		} else if(node.IsScalar()) {
			std::string str_vector = node.as<std::string>();
			sscanf(str_vector.c_str(), "%i,%i", &vector.x, &vector.y);
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Vector2<size_t> >::decode(const YAML::Node& node, sf::Vector2<size_t>& vector) {
		if(node.IsSequence()) {
			vector.x = node[0].as<size_t>();
			vector.y = node[1].as<size_t>();
		} else if(node.IsScalar()) {
			std::string str_vector = node.as<std::string>();
			sscanf(str_vector.c_str(), "%zu,%zu", &vector.x, &vector.y);
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Color>::decode(const YAML::Node& node, sf::Color& color) {
		if(node.IsSequence()) {
			if(node.size() >= 3) {
				color.r = node[0].as<int>();
				color.g = node[1].as<int>();
				color.b = node[2].as<int>();
				if(node.size() > 3) {
					color.a = node[3].as<int>();
				} else {
					color.a = 255;
				}
			}
		} else if(node.IsScalar()) {
			std::string str_color = node.as<std::string>();
			
			std::map<std::string, sf::Color> color_map{
				{"black",       sf::Color::Black},
				{"white",       sf::Color::White},
				{"red",         sf::Color::Red},
				{"green",       sf::Color::Green},
				{"blue",        sf::Color::Blue},
				{"yellow",      sf::Color::Yellow},
				{"magenta",     sf::Color::Magenta},
				{"cyan",        sf::Color::Cyan},
				{"transparent", sf::Color::Transparent},
				{"null-color",  {255, 255, 255, 0}}
			};
			
			if(color_map.find(str_color) != color_map.end()) {
				color = color_map[str_color];
				return true;
			}
			
			unsigned r{0}, g{0}, b{0}, a{255};
			if(str_color.size() == 8) {
				sscanf(str_color.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
			} else if(str_color.size() == 6) {
				sscanf(str_color.c_str(), "%02x%02x%02x", &r, &g, &b);
			} else {
				throw YAML::BadConversion{node.Mark()};
			}
			color = {sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)};
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Text::Style>::decode(const YAML::Node& node, sf::Text::Style& style) {
		std::map<std::string, sf::Text::Style> style_map{
			{"Regular",       sf::Text::Style::Regular},
			{"Bold",          sf::Text::Style::Bold},
			{"Italic",        sf::Text::Style::Italic},
			{"Underlined",    sf::Text::Style::Underlined},
			{"StrikeThrough", sf::Text::Style::StrikeThrough},
		};
		
		if(node.IsScalar()) {
			std::string str_style = node.as<std::string>();
			style = style_map[str_style];
		} else if(node.IsSequence()) {
			style = sf::Text::Style::Regular;
			std::string str_style;
			for(const auto& item: node) {
				str_style = item.as<std::string>();
				style = static_cast<sf::Text::Style>(style | style_map[str_style]);
			}
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Mouse::Button>::decode(const YAML::Node& node, sf::Mouse::Button& button) {
		if(node.as<std::string>() == "right")
			button = sf::Mouse::Button::Right;
		else if(node.as<std::string>() == "left")
			button = sf::Mouse::Button::Left;
		else if(node.as<std::string>() == "middle")
			button = sf::Mouse::Button::Middle;
		else if(node.as<std::string>() == "button-count")
			button = sf::Mouse::Button::ButtonCount;
		else if(node.as<std::string>() == "x-button-1")
			button = sf::Mouse::Button::XButton1;
		else if(node.as<std::string>() == "x-button-2")
			button = sf::Mouse::Button::XButton2;
		else
			throw YAML::BadConversion{node.Mark()};
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	bool Decode<sf::Shader>::decode(const YAML::Node& node, sf::Shader& shader) {
		std::string vert;
		std::string frag;
		if(node["vert"] && node["frag"]) {
			node["vert"] >> vert;
			node["frag"] >> frag;
			shader.loadFromFile(vert, frag);
		} else {
			if(node["vert"]) {
				node["vert"] >> vert;
				shader.loadFromFile(vert, sf::Shader::Vertex);
			} else if(node["frag"]) {
				node["frag"] >> frag;
				shader.loadFromFile(frag, sf::Shader::Fragment);
			} else {
				throw YAML::BadConversion{node.Mark()};
			}
		}
		return true;

	}
	*/
}
