#include "ieml-sfml.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ieml {
	auto Decode<char, sf::String>::decode(ieml::Node const& node) -> orl::Option<sf::String> {
		auto str{node.as<ie::ParseString>().except().str};
		return ie::to_utf32(ie::to_utf32(str));
	}
	
	auto Decode<char, sf::Color>::decode(ieml::Node const& node) -> orl::Option<sf::Color> {
		auto& clear_node{node.get_clear()};
		for(auto list: clear_node.get_list_view().ok_or_none()) {
			return sf::Color{
				list.at(0).except().as<uint8_t>().except(),
				list.at(1).except().as<uint8_t>().except(),
				list.at(2).except().as<uint8_t>().except(),
				list.get_as<uint8_t>(3).except().ok_or(255)
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
	
	auto Decode<char, ie::LoadTextStyle>::decode(ieml::Node const& node) -> orl::Option<ie::LoadTextStyle> {
		auto& clear_node{node.get_clear()};
		for(auto& list: clear_node.get_list().ok_or_none()) {
			sf::Text::Style result{sf::Text::Style::Regular};
			for(auto& item: list) {
				result = static_cast<sf::Text::Style>(result | item.as<ie::LoadTextStyle>().except().style);
			}
			return {{result}};
		}
		auto& str{clear_node.get_raw().except().str};
		if(str == "regular") {
			return {{sf::Text::Style::Regular}};
		} else if(str == "bold") {
			return {{sf::Text::Style::Bold}};
		} else if(str == "italic") {
			return {{sf::Text::Style::Italic}};
		} else if(str == "underlined") {
			return {{sf::Text::Style::Underlined}};
		} else if(str == "strike-through") {
			return {{sf::Text::Style::StrikeThrough}};
		}
		return {};
	}
	
	auto Decode<char, sf::Mouse::Button>::decode(ieml::Node const& node) -> orl::Option<sf::Mouse::Button> {
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
	
	auto Decode<char, ie::LoadShader>::decode(ieml::Node const& node) -> orl::Option<ie::LoadShader> {
		return ie::LoadShader::decode(node);
	}
}
