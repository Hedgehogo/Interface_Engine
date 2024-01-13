#pragma once

#include "IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/OnlyDrawable.hpp"
#include "IE/component/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "IE/shared/SReader/SReader.hpp"

namespace ie {
	class VideoFromFile : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			std::vector<sf::Texture> video;
			MakeDyn<ISRFloat> viewing_progress;
			
			Make(std::vector<sf::Texture> video, MakeDyn<ISRFloat> viewing_progress);
			
			VideoFromFile* make(InitInfo init_info) override;
		};
		
		VideoFromFile(Make&& make, InitInfo init_info);
		
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
		SReader<ISRFloat> viewing_progress;
	};
}