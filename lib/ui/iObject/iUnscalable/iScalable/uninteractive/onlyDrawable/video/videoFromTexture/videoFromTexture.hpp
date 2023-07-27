#pragma once

#include "../../onlyDrawable.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"

namespace ui {
	class VideoFromTexture : public OnlyDrawable {
	public:
		VideoFromTexture(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect = {0, 0, 0, 0}, int countFrame = 0, sf::Vector2i offset = {0, 0});
		
		void setCurrentFrame(float viewingProgress);
		
		void draw() override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		VideoFromTexture* copy() override;
	
	protected:
		sf::IntRect rect;
		sf::Vector2i offset;
		PSCoefficient viewingProgress;
		sf::Sprite sprite;
		sf::Vector2i textureSize;
		sf::Vector2f size;
		int countFrame;
	};
}