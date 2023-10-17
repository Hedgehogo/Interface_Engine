#pragma once

#include "IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/OnlyDrawable.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"
#include "IE/component/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"

namespace ie {
	class VideoFromFile : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
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