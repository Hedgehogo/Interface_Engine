#include "VideoFromTexture.hpp"

namespace ie {
	VideoFromTexture::Make::Make(
		const sf::Texture& texture,
		MakeDyn<ISRFloat> viewing_progress,
		sf::IntRect rect,
		size_t frame_count,
		sf::Vector2i offset
	) :
		texture(texture), viewing_progress(std::move(viewing_progress)), rect(rect), frame_count(frame_count), offset(offset) {
	}
	
	VideoFromTexture::Make::Make(const sf::Texture& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count) :
		texture(texture), viewing_progress(std::move(viewing_progress)), rect(rect), frame_count(frame_count), offset(this->rect.width, 0) {
	}
	
	VideoFromTexture::Make::Make(const sf::Texture& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect) :
		texture(texture),
		viewing_progress(std::move(viewing_progress)),
		rect(rect),
		frame_count(this->texture.getSize().x / this->rect.width),
		offset(this->rect.width, 0) {
	}
	
	VideoFromTexture* VideoFromTexture::Make::make(InitInfo init_info) {
		return new VideoFromTexture{std::move(*this), init_info};
	}
	
	VideoFromTexture::VideoFromTexture(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		rect(make.rect),
		offset(make.offset),
		viewing_progress(
			make.viewing_progress.make(init_info.dyn_buffer),
			[this](float value) {
				set_current_frame(value);
			}
		),
		sprite(make.texture, make.rect),
		texture_size(make.texture.getSize()),
		frame_count(make.frame_count) {
		viewing_progress.get().set_bounds(0, 1);
	}
	
	void VideoFromTexture::set_current_frame(float viewing_progress) {
		sprite.setTextureRect(
			{
				(offset * static_cast<int>(viewing_progress * frame_count)) + sf::Vector2i{rect.left, rect.top},
				{rect.width, rect.height}
			}
		);
	}
	
	void VideoFromTexture::draw() {
		render_target->draw(sprite);
	}
	
	sf::Vector2f VideoFromTexture::get_area_position() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f VideoFromTexture::get_area_size() const {
		return size;
	}
	
	sf::Vector2f VideoFromTexture::get_min_size() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromTexture::get_normal_size() const {
		return sf::Vector2f{sf::Vector2i{rect.width, rect.height}};
	}
	
	void VideoFromTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		sprite.setPosition(position);
		sprite.setScale(size / sf::Vector2f{sf::Vector2i{rect.width, rect.height}});
	}
}