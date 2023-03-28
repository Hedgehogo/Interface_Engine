#pragma once

#include "../../onlyDrawable.hpp"

namespace ui {
	class VideoFromTexture : public OnlyDrawable{
		sf::IntRect rect;
		sf::Vector2i offset;
		PSCoefficient viewingProgress;
		sf::Sprite sprite;
		sf::Vector2i textureSize;
		sf::Vector2f size;
		int countFrame;

	public:
		VideoFromTexture(sf::Texture &texture, PSCoefficient viewingProgress, sf::IntRect rect = {0, 0, 0, 0}, int countFrame = 0, sf::Vector2i offset = {0, 0});

		void setCurrentFrame(float viewingProgress);

		void draw() override;

		sf::Vector2f getAreaPosition() override;

		sf::Vector2f getAreaSize() override;

		sf::Vector2f getMinSize() override;

		sf::Vector2f getNormalSize() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		VideoFromTexture *copy() override;
	};
}