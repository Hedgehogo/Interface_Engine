#include "ieml-sfml.hpp"

namespace ieml {
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, orl::Option<sf::Vector2<T> > >
	decode_vector2_str(BasicStringCIter<char> first, BasicStringCIter<char> last) {
		number::Parser<char, T> x_parser{std::move(first), std::move(last)};
		auto x{x_parser.parse_number_scientific()};
		if(x.is_some() && first != last && *first == ',' && (first + 1) != last && *(first + 1) == ' ') {
			number::Parser<char, T> y_parser{std::move(x_parser.pos() + 2), std::move(last)};
			auto y{y_parser.parse_number_scientific()};
			y_parser.skip_blank_line();
			if(y.is_some() && y_parser.is_complete()) {
				return sf::Vector2<T>{x.some(), y.some()};
			}
		}
		return {};
	}
	
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, orl::Option<sf::Vector2<T> > >
	decode_vector2(ieml::Node const& node) {
		auto& clear_node = node.get_clear();
		if(clear_node.get_type() == NodeType::List) {
			return sf::Vector2<T>{
				node.at(0).except().as<T>().except(),
				node.at(1).except().as<T>().except(),
			};
		}
		auto& str{clear_node.get_string().except()};
		return decode_vector2_str<T>(str.cbegin(), str.cend());
	}
	
	orl::Option<sf::Vector2<float> > Decode<char, sf::Vector2<float> >::decode(ieml::Node const& node) {
		return decode_vector2<float>(node);
	}
	
	orl::Option<sf::Vector2<int> > Decode<char, sf::Vector2<int> >::decode(ieml::Node const& node) {
		return decode_vector2<int>(node);
	}
	
	orl::Option<sf::Vector2<size_t> > Decode<char, sf::Vector2<size_t> >::decode(ieml::Node const& node) {
		return decode_vector2<size_t>(node);
	}
	
	orl::Option<sf::Color> Decode<char, sf::Color>::decode(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(clear_node.get_type() == NodeType::List) {
			return sf::Color{
				node.at(0).except().as<uint8_t>(),
				node.at(0).except().as<uint8_t>(),
				node.at(0).except().as<uint8_t>(),
				node.get_as<uint8_t>(0).ok_or(255)
			};
		}
		auto& str{clear_node.get_string().except()};
		if(str == "black") {
			return sf::Color::Black;
		} else if(str == "white") {
			return sf::Color::White;
		} else if(str == "red") {
			return sf::Color::Red;
		} else if(str == "green") {
			return sf::Color::Green;
		} else if(str == "blue") {
			return sf::Color::Blue;
		} else if(str == "yellow") {
			return sf::Color::Yellow;
		} else if(str == "magenta") {
			return sf::Color::Magenta;
		} else if(str == "cyan") {
			return sf::Color::Cyan;
		} else if(str == "transparent") {
			return sf::Color::Transparent;
		}
		unsigned r, g, b, a{255};
		if(str.size() == 8) {
			sscanf(str.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
		} else if(str.size() == 6) {
			sscanf(str.c_str(), "%02x%02x%02x", &r, &g, &b);
		} else {
			return {};
		}
		return sf::Color{uint8_t(r), uint8_t(g), uint8_t(b), uint8_t(a)};
	}
	
	orl::Option<sf::Text::Style> Decode<char, sf::Text::Style>::decode(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(auto scalar{clear_node.get_string()}) {
			auto& str{scalar.ok()};
			if(str == "Regular") {
				return sf::Text::Style::Regular;
			} else if(str == "Bold") {
				return sf::Text::Style::Bold;
			} else if(str == "Italic") {
				return sf::Text::Style::Italic;
			} else if(str == "Underlined") {
				return sf::Text::Style::Underlined;
			} else if(str == "StrikeThrough") {
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
