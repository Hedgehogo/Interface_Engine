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
			PSCoefficient viewing_progress;
			
			Make(std::vector<sf::Texture> video, PSCoefficient viewing_progress);
			
			VideoFromFile* make(InitInfo init_info) override;
		};
		
		VideoFromFile(Make&& make, InitInfo init_info);
		
		VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewing_progress);
		
		void set_current_frame(float viewing_progress);
		
		void draw() override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		VideoFromFile* copy() override;
	
	protected:
		sf::Vector2i size_video;
		sf::Vector2f size;
		std::string path;
		
		std::vector<sf::Texture> buffer_texture;
		sf::Sprite sprite;
		PSCoefficient viewing_progress;
	};
}