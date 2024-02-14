#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "../../OnlyDrawable.hpp"

namespace ie {
	class VideoFromTexture : public OnlyDrawable {
	public:
		struct Make : public virtual INonInteractive::Make {
			BoxPtr<IScalable::Make> object;
			const sf::Texture& texture;
			MakeDyn<ISRFloat> viewing_progress;
			sf::IntRect rect = {};
			size_t frame_count = 0;
			sf::Vector2i offset = {};
			
			Make(const sf::Texture& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count, sf::Vector2i offset);
			
			Make(const sf::Texture& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count);
			
			Make(const sf::Texture& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect);
			
			VideoFromTexture* make(InitInfo init_info) override;
		};
		
		VideoFromTexture(Make&& make, InitInfo init_info);
		
		void set_current_frame(float viewing_progress);
		
		void draw() override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
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