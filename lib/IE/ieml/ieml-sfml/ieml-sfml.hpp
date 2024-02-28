#pragma once

#include <SFML/Graphics.hpp>
#include "LoadShader/LoadShader.hpp"
#include "LoadTextStyle/LoadTextStyle.hpp"
#include "../ieml-basic/ieml-basic.hpp"

namespace tnl {
	template<>
	struct TypeName<sf::String> {
		constexpr static auto type_name = StringView{"String32"};
	};
	
	template<typename T>
	struct TypeName<sf::Vector2<T> > {
		static auto type_name() -> StringView;
	};
	
	template<typename T>
	struct TypeName<sf::Rect<T> > {
		static auto type_name() -> StringView;
	};
	
	template<>
	struct TypeName<sf::Color> {
		constexpr static auto type_name = StringView{"Color"};
	};
	
	template<>
	struct TypeName<ie::LoadTextStyle> {
		constexpr static auto type_name = StringView{"TextStyle"};
	};
	
	template<>
	struct TypeName<sf::Mouse::Button> {
		constexpr static auto type_name = StringView{"MouseButton"};
	};
	
	template<>
	struct TypeName<ie::LoadShader> {
		constexpr static auto type_name = StringView{"Shader"};
	};
}

namespace ieml {
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
