#include "VideoFromFile.hpp"

namespace ie {
	VideoFromFile::Make::Make(std::vector<sf::Texture> video, MakeDyn<ISRFloat> viewing_progress) :
		video(std::move(video)), viewing_progress(std::move(viewing_progress)) {
	}
	
	auto VideoFromFile::Make::make(InitInfo init_info) -> VideoFromFile* {
		return new VideoFromFile{std::move(*this), init_info};
	}
	
	VideoFromFile::VideoFromFile(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		size_video_(make.video[0].getSize()),
		buffer_texture_(make.video),
		viewing_progress_(
			make.viewing_progress.make(SInitInfo{init_info}),
			[this](float value) {
				set_current_frame(value);
			}
		) {
		viewing_progress_.get().set_bounds(0., 1.);
		sprite_.setTexture(buffer_texture_[0]);
	}
	
	auto VideoFromFile::set_current_frame(float viewing_progress) -> void {
		if(viewing_progress >= 1) {
			sprite_.setTexture(buffer_texture_[buffer_texture_.size()]);
			return;
		}
		if(viewing_progress <= 0) {
			sprite_.setTexture(buffer_texture_[0]);
			return;
		}
		sprite_.setTexture(buffer_texture_[buffer_texture_.size() * viewing_progress]);
	}
	
	auto VideoFromFile::draw() -> void {
		render_target_->draw(sprite_);
	}
	
	auto VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		this->size_ = size;
		sprite_.setPosition(position);
		sprite_.setScale(div_xy(size, sf::Vector2f{size_video_}));
	}
	
	auto VideoFromFile::get_area_position() const -> sf::Vector2f {
		return sprite_.getPosition();
	}
	
	auto VideoFromFile::get_area_size() const -> sf::Vector2f {
		return size_;
	}
	
	auto VideoFromFile::get_min_size() const -> sf::Vector2f {
		return {0, 0};
	}
	
	auto VideoFromFile::get_normal_size() const -> sf::Vector2f {
		return sf::Vector2f{size_video_};
	}
}