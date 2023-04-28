#pragma once

#include "ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/onlyDrawable.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"
#include "ui/updatable/iUpdatable/iUpdatable.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	class VideoFromFile : public OnlyDrawable {
	protected:
		sf::Vector2i sizeVideo;
		sf::Vector2f size;
		std::string path;
		
		std::vector<sf::Texture> bufferTexture;
		sf::Sprite sprite;
		PSCoefficient viewingProgress;
	
	public:
		VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewingProgress);
		
		void setCurrentFrame(float viewingProgress);
		
		void draw() override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	
	public:
		VideoFromFile* copy() override;
	};
}