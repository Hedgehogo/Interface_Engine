#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	template<typename T, T (* Fn)(T)>
	sf::Vector2<T> map_vector2(sf::Vector2<T> value) {
		return {Fn(value.x), Fn(value.y)};
	}
	
	template<typename T>
	sf::Vector2<T> mul_xy(sf::Vector2<T> first, sf::Vector2<T> second) {
		return {first.x * second.x, first.y * second.y};
	}
	
	template<typename T>
	sf::Vector2<T> div_xy(sf::Vector2<T> first, sf::Vector2<T> second) {
		return {first.x / second.x, first.y / second.y};
	}
}
