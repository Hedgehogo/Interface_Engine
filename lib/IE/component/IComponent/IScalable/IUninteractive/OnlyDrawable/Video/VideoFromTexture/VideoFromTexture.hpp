#pragma once

#include "../../OnlyDrawable.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"

namespace ie {
	class VideoFromTexture : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			BoxPtr<IScalable::Make> object;
			const sf::Texture& texture;
			PSCoefficient viewing_progress;
			sf::IntRect rect = {};
			size_t frame_count = 0;
			sf::Vector2i offset = {};
			
			Make(const sf::Texture& texture, PSCoefficient viewing_progress, sf::IntRect rect, size_t frame_count, sf::Vector2i offset);
			
			Make(const sf::Texture& texture, PSCoefficient viewing_progress, sf::IntRect rect, size_t frame_count);
			
			Make(const sf::Texture& texture, PSCoefficient viewing_progress, sf::IntRect rect);
			
			VideoFromTexture* make(InitInfo init_info) override;
		};
		
		VideoFromTexture(Make&& make, InitInfo init_info);
		
		VideoFromTexture(const sf::Texture& texture, PSCoefficient viewing_progress, sf::IntRect rect = {}, size_t frame_count = 0, sf::Vector2i offset = {});
		
		void set_current_frame(float viewing_progress);
		
		void draw() override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		VideoFromTexture* copy() override;
	
	protected:
		sf::IntRect rect;
		sf::Vector2i offset;
		PSCoefficient viewing_progress;
		sf::Sprite sprite;
		sf::Vector2i texture_size;
		sf::Vector2f size;
		size_t frame_count;
	};
}