#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "../../OnlyDrawable.hpp"

namespace ie {
	class VideoFromTexture : public OnlyDrawable {
	public:
		struct Make : public virtual INonInteractive::Make {
			BoxPtr<IScalable::Make> object;
			sf::Texture const& texture;
			MakeDyn<ISRFloat> viewing_progress;
			sf::IntRect rect = {};
			size_t frame_count = 0;
			sf::Vector2i offset = {};
			
			Make(sf::Texture const& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count, sf::Vector2i offset);
			
			Make(sf::Texture const& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count);
			
			Make(sf::Texture const& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect);
			
			auto make(InitInfo init_info) -> VideoFromTexture* override;
		};
		
		VideoFromTexture(Make&& make, InitInfo init_info);
		
		auto set_current_frame(float viewing_progress) -> void;
		
		auto draw() -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
	protected:
		sf::IntRect rect_;
		sf::Vector2i offset_;
		SReader<ISRFloat> viewing_progress_;
		sf::Sprite sprite_;
		sf::Vector2i texture_size_;
		sf::Vector2f size_;
		size_t frame_count_;
	};
}