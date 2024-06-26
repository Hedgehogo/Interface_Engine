#include "VideoFromTexture.hpp"

namespace ie {
	VideoFromTexture::Make::Make(
		sf::Texture const& texture,
		MakeDyn<ISRFloat> viewing_progress,
		sf::IntRect rect,
		size_t frame_count,
		sf::Vector2i offset
	) :
		texture(texture), viewing_progress(std::move(viewing_progress)), rect(rect), frame_count(frame_count), offset(offset) {
	}
	
	VideoFromTexture::Make::Make(sf::Texture const& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect, size_t frame_count) :
		texture(texture), viewing_progress(std::move(viewing_progress)), rect(rect), frame_count(frame_count), offset(this->rect.width, 0) {
	}
	
	VideoFromTexture::Make::Make(sf::Texture const& texture, MakeDyn<ISRFloat> viewing_progress, sf::IntRect rect) :
		texture(texture),
		viewing_progress(std::move(viewing_progress)),
		rect(rect),
		frame_count(this->texture.getSize().x / this->rect.width),
		offset(this->rect.width, 0) {
	}
	
	auto VideoFromTexture::Make::make(InitInfo init_info) -> VideoFromTexture* {
		return new VideoFromTexture{std::move(*this), init_info};
	}
	
	VideoFromTexture::VideoFromTexture(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		rect_(make.rect),
		offset_(make.offset),
		viewing_progress_(
			make.viewing_progress.make(SInitInfo{init_info}),
			[this](float value) {
				set_current_frame(value);
			}
		),
		sprite_(make.texture, make.rect),
		texture_size_(make.texture.getSize()),
		frame_count_(make.frame_count) {
		viewing_progress_.get().set_bounds(0, 1);
	}
	
	auto VideoFromTexture::set_current_frame(float viewing_progress) -> void {
		sprite_.setTextureRect(
			{
				(offset_ * static_cast<int>(viewing_progress * frame_count_)) + sf::Vector2i{rect_.left, rect_.top},
				{rect_.width, rect_.height}
			}
		);
	}
	
	auto VideoFromTexture::draw() -> void {
		render_target_->draw(sprite_);
	}
	
	auto VideoFromTexture::get_area_position() const -> sf::Vector2f {
		return sprite_.getPosition();
	}
	
	auto VideoFromTexture::get_area_size() const -> sf::Vector2f {
		return size_;
	}
	
	auto VideoFromTexture::get_min_size() const -> sf::Vector2f {
		return {0, 0};
	}
	
	auto VideoFromTexture::get_normal_size() const -> sf::Vector2f {
		return sf::Vector2f{sf::Vector2i{rect_.width, rect_.height}};
	}
	
	auto VideoFromTexture::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		this->size_ = size;
		sprite_.setPosition(position);
		sprite_.setScale(div_xy(size, sf::Vector2f{sf::Vector2i{rect_.width, rect_.height}}));
	}
}