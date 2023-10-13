#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	template<typename T, T (* Fn)(T)>
	sf::Vector2<T> mapVector2(sf::Vector2<T> value) {
		return {Fn(value.x), Fn(value.y)};
	}
}
