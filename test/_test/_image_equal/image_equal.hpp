#pragma once
#include <filesystem>
#include <SFML/Graphics/Texture.hpp>

bool image_equal(const sf::Image& first, const sf::Image& second, float precision);
