#pragma once

#include <SFML/Graphics.hpp>
#include <IEML/node.hpp>
#include "LoadShader/LoadShader.hpp"
#include "LoadString//LoadString.hpp"
#include "LoadTextStyle/LoadTextStyle.hpp"

namespace ieml {
	template<typename T>
	struct Decode<char, orl::Option<T> > {
		static orl::Option<orl::Option<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, std::vector<T> > {
		static orl::Option<std::vector<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, absl::flat_hash_map<std::string, T> > {
		static orl::Option<absl::flat_hash_map<std::string, T> > decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, ie::LoadString> {
		static orl::Option<ie::LoadString> decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, sf::String> {
		static orl::Option<sf::String> decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, sf::Vector2<T> > {
		static orl::Option<sf::Vector2<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, sf::Rect<T> > {
		static orl::Option<sf::Rect<T> > decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, sf::Color> {
		static orl::Option<sf::Color> decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, ie::LoadTextStyle> {
		static orl::Option<ie::LoadTextStyle> decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, sf::Mouse::Button> {
		static orl::Option<sf::Mouse::Button> decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, ie::LoadShader> {
		static orl::Option<ie::LoadShader> decode(ieml::Node const& node);
	};
}

#include "ieml-sfml.inl"
