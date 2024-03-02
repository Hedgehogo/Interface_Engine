#pragma once

#include "IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/OnlyDrawable.hpp"
#include "IE/component/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"

namespace ie {
	class VideoFromFile : public OnlyDrawable {
	public:
		struct Make : public virtual INonInteractive::Make {
			std::vector<sf::Texture> video;
			MakeDyn<ISRFloat> viewing_progress;
			
			Make(std::vector<sf::Texture> video, MakeDyn<ISRFloat> viewing_progress);
			
			auto make(InitInfo init_info) -> VideoFromFile* override;
		};
		
		VideoFromFile(Make&& make, InitInfo init_info);
		
		auto set_current_frame(float viewing_progress) -> void;
		
		auto draw() -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
	protected:
		sf::Vector2i size_video_;
		sf::Vector2f size_;
		std::string path_;
		
		std::vector<sf::Texture> buffer_texture_;
		sf::Sprite sprite_;
		SReader<ISRFloat> viewing_progress_;
	};
}