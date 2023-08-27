#pragma once

#include <gtest/gtest.h>
#include "../../lib/IE/IE.hpp"

struct Program{
    sf::RenderTexture renderTexture;
    ie::Interface *interface;

    Program(ie::Interface *interface, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

    Program(ie::IScalable *object, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

	Program(std::string path, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

	~Program();
};

bool operator == (const sf::Texture & texture1, const sf::Texture& texture2);