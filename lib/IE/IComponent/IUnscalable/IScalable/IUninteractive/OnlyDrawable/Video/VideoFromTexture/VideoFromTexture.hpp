#pragma once

#include "../../OnlyDrawable.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"

namespace ui {
	class VideoFromTexture : public OnlyDrawable {
	public:
		struct Make : public IUninteractive::Make {
			BoxPtr<IScalable::Make> object;
			const sf::Texture& texture;
			PSCoefficient viewingProgress;
			sf::IntRect rect = {};
			std::size_t countFrame = 0;
			sf::Vector2i offset = {};
			
			Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, std::size_t countFrame, sf::Vector2i offset);
			
			Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, std::size_t countFrame);
			
			Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect);
			
			VideoFromTexture* make(InitInfo initInfo) override;
		};
		
		VideoFromTexture(Make&& make, InitInfo initInfo);
		
		VideoFromTexture(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect = {}, std::size_t countFrame = 0, sf::Vector2i offset = {});
		
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
		std::size_t countFrame;
	};
}