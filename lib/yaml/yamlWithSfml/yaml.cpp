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
			{"Black", sf::Color::Black},
			{"White", sf::Color::White},
			{"Red", sf::Color::Red},
			{"Green", sf::Color::Green},
			{"Blue", sf::Color::Blue},
			{"Yellow", sf::Color::Yellow},
			{"Magenta", sf::Color::Magenta},
			{"Cyan", sf::Color::Cyan},
			{"Transparent", sf::Color::Transparent}
		};
		
		if(colorMap.find(strColor) != colorMap.end()) {
			color = colorMap[strColor];
			return;
		}
		
		uint r{0}, g{0}, b{0}, a{255};
		if(strColor.size() == 8) {
			sscanf(strColor.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
		} else if(strColor.size() == 6) {
			sscanf(strColor.c_str(), "%02x%02x%02x", &r, &g, &b);
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
	} else if(node.IsSequence()) {
		style = sf::Text::Style::Regular;
		std::string strStyle;
		for(const auto &item: node) {
			strStyle = item.as<std::string>();
			style = static_cast<sf::Text::Style>(style | styleMap[strStyle]);
		}
	}
}