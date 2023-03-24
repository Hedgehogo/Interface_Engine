#pragma once

#include <gtest/gtest.h>
#include "../../lib/ui/UI.hpp"

struct Program{
    sf::RenderTexture renderTexture;
    ui::Interface *interface;

    Program(ui::Interface *interface, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

    Program(ui::IScalable *object, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

	Program(std::string path, sf::Vector2u size = {0, 0}, sf::Vector2f mousePosition = {0, 0});

	~Program();
};

bool operator == (const sf::Texture & texture1, const sf::Texture& texture2);