#include "yaml.hpp"

void operator>>(const YAML::Node &node, sf::Vector2<float> &vector) {
	if(node.IsSequence()) {
		vector.x = node[0].as<float>();
		vector.y = node[1].as<float>();
	} else if(node.IsScalar()) {
		std::string strVector = node.as<std::string>();
		sscanf(strVector.c_str(), "%f,%f", &vector.x, &vector.y);
	}
}

void operator>>(const YAML::Node &node, sf::Vector2<int> &vector) {
	if(node.IsSequence()) {
		vector.x = node[0].as<int>();
		vector.y = node[1].as<int>();
	} else if(node.IsScalar()) {
		std::string strVector = node.as<std::string>();
		sscanf(strVector.c_str(), "%i,%i", &vector.x, &vector.y);
	}
}

void operator>>(const YAML::Node &node, sf::Vector2<uint> &vector) {
	if(node.IsSequence()) {
		vector.x = node[0].as<uint>();
		vector.y = node[1].as<uint>();
	} else if(node.IsScalar()) {
		std::string strVector = node.as<std::string>();
		sscanf(strVector.c_str(), "%u,%u", &vector.x, &vector.y);
	}
}

void operator>>(const YAML::Node &node, sf::Color &color) {
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
		std::string strColor = node.as<std::string>();
		
		std::map<std::string, sf::Color> colorMap {
			{"black", sf::Color::Black},
			{"white", sf::Color::White},
			{"red", sf::Color::Red},
			{"green", sf::Color::Green},
			{"blue", sf::Color::Blue},
			{"yellow", sf::Color::Yellow},
			{"magenta", sf::Color::Magenta},
			{"cyan", sf::Color::Cyan},
			{"transparent", sf::Color::Transparent},
            {"null-color", {255, 255, 255, 0}}
		};
		
		if(colorMap.find(strColor) != colorMap.end()) {
			color = colorMap[strColor];
			return;
		}
		
		uint r{0}, g{0}, b{0}, a{255};
		if (strColor.size() == 8) {
			sscanf(strColor.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
		} else if (strColor.size() == 6) {
			sscanf(strColor.c_str(), "%02x%02x%02x", &r, &g, &b);
		} else {
            throw YAML::BadConversion{node.Mark()};
        }
		color = {sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)};
	}
}

void operator>>(const YAML::Node &node, sf::Text::Style& style) {
	std::map<std::string, sf::Text::Style> styleMap {
		{"Regular", sf::Text::Style::Regular},
		{"Bold", sf::Text::Style::Bold},
		{"Italic", sf::Text::Style::Italic},
		{"Underlined", sf::Text::Style::Underlined},
		{"StrikeThrough", sf::Text::Style::StrikeThrough},
	};
	
	if(node.IsScalar()) {
		std::string strStyle = node.as<std::string>();
		style = styleMap[strStyle];
	} else if (node.IsSequence()) {
		style = sf::Text::Style::Regular;
		std::string strStyle;
		for(const auto &item: node) {
			strStyle = item.as<std::string>();
			style = static_cast<sf::Text::Style>(style | styleMap[strStyle]);
		}
	} else {
        throw YAML::BadConversion{node.Mark()};
    }
}

void operator >>(const YAML::Node& node, sf::Mouse::Button& button){
    if (node.as<std::string>() == "right") button = sf::Mouse::Button::Right;
    else if (node.as<std::string>() == "left") button = sf::Mouse::Button::Left;
    else if (node.as<std::string>() == "middle") button = sf::Mouse::Button::Middle;
    else if (node.as<std::string>() == "button-count") button = sf::Mouse::Button::ButtonCount;
    else if (node.as<std::string>() == "x-button-1") button = sf::Mouse::Button::XButton1;
    else if (node.as<std::string>() == "x-button-2") button = sf::Mouse::Button::XButton2;
    else throw YAML::BadConversion{node.Mark()};
}

void operator >>(const YAML::Node& node, sf::Shader& shader){
    std::string vert;
    std::string frag;
    if (node["vert"] && node["frag"]){
        node["vert"] >> vert;
        node["frag"] >> frag;
        shader.loadFromFile(vert, frag);
    } else {
        if (node["vert"]){
            node["vert"] >> vert;
            shader.loadFromFile(vert, sf::Shader::Vertex);
        } else if (node["frag"]){
            node["frag"] >> frag;
            shader.loadFromFile(frag, sf::Shader::Fragment);
        } else {
			throw YAML::BadConversion{node.Mark()};
		}
    }
}

bool createBoolFromYaml(const YAML::Node &node, std::string trueValue, std::string falseValue) {
	std::string parameter{node.as<std::string>()};
	
	if(parameter == trueValue) return true;
	else if(parameter == falseValue) return false;
	else throw YAML::BadConversion{node.Mark()};
}
