#pragma once

#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/OnlyDrawable.hpp"
#include "IE/Modules/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"
#include "IE/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	class VideoFromFile : public OnlyDrawable {
	public:
		struct Make : public IUninteractive::Make {
			std::vector<sf::Texture> video;
			PSCoefficient viewingProgress;
			
			Make(std::vector<sf::Texture> video, PSCoefficient viewingProgress);
			
			VideoFromFile* make(InitInfo initInfo) override;
		};
		
		VideoFromFile(Make&& make, InitInfo initInfo);
		
		VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewingProgress);
		
		void setCurrentFrame(float viewingProgress);
		
		void draw() override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		VideoFromFile* copy() override;
	
	protected:
		sf::Vector2i sizeVideo;
		sf::Vector2f size;
		std::string path;
		
		std::vector<sf::Texture> bufferTexture;
		sf::Sprite sprite;
		PSCoefficient viewingProgress;
	};
}