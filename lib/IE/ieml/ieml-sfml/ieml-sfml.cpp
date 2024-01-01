#include "ieml-sfml.hpp"

namespace ieml {
	orl::Option<sf::Color> Decode<char, sf::Color>::decode(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(auto list{clear_node.get_list_view()}) {
			return sf::Color{
				list.ok().at(0).except().as<uint8_t>(),
				list.ok().at(0).except().as<uint8_t>(),
				list.ok().at(0).except().as<uint8_t>(),
				list.ok().get_as<uint8_t>(0).ok_or(255)
			};
		}
		auto& raw{clear_node.get_raw().except().str};
		if(raw == "black") {
			return sf::Color::Black;
		} else if(raw == "white") {
			return sf::Color::White;
		} else if(raw == "red") {
			return sf::Color::Red;
		} else if(raw == "green") {
			return sf::Color::Green;
		} else if(raw == "blue") {
			return sf::Color::Blue;
		} else if(raw == "yellow") {
			return sf::Color::Yellow;
		} else if(raw == "magenta") {
			return sf::Color::Magenta;
		} else if(raw == "cyan") {
			return sf::Color::Cyan;
		} else if(raw == "transparent") {
			return sf::Color::Transparent;
		}
		unsigned r, g, b, a{255};
		if(raw.size() == 8) {
			sscanf(raw.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
		} else if(raw.size() == 6) {
			sscanf(raw.c_str(), "%02x%02x%02x", &r, &g, &b);
		} else {
			return {};
		}
		return sf::Color{uint8_t(r), uint8_t(g), uint8_t(b), uint8_t(a)};
	}
	
	orl::Option<sf::Text::Style> Decode<char, sf::Text::Style>::decode(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(auto scalar{clear_node.get_string()}) {
			auto& str{scalar.ok()};
			if(str == "regular") {
				return sf::Text::Style::Regular;
			} else if(str == "bold") {
				return sf::Text::Style::Bold;
			} else if(str == "italic") {
				return sf::Text::Style::Italic;
			} else if(str == "underlined") {
				return sf::Text::Style::Underlined;
			} else if(str == "strike-through") {
				return sf::Text::Style::StrikeThrough;
			}
		} else {
			auto& list{clear_node.get_list().except()};
			sf::Text::Style result{sf::Text::Style::Regular};
			for(auto& item: list) {
				result = static_cast<sf::Text::Style>(result | item.as<sf::Text::Style>().except());
			}
			return result;
		}
		return {};
	}
	
	orl::Option<sf::Mouse::Button> Decode<char, sf::Mouse::Button>::decode(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		auto& str{clear_node.get_string().except()};
		if(str == "right") {
			return sf::Mouse::Button::Right;
		} else if(str == "left") {
			return sf::Mouse::Button::Left;
		} else if(str == "middle") {
			return sf::Mouse::Button::Middle;
		} else if(str == "button-count") {
			return sf::Mouse::Button::ButtonCount;
		} else if(str == "x-button-1") {
			return sf::Mouse::Button::XButton1;
		} else if(str == "x-button-2") {
			return sf::Mouse::Button::XButton2;
		}
		return {};
	}
	
	orl::Option<ie::LoadShader> Decode<char, ie::LoadShader>::decode(ieml::Node const& node) {
		return ie::LoadShader::decode(node);
	}
}
