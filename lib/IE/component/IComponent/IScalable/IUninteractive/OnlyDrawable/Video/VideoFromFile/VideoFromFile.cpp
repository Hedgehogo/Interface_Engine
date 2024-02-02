#include "VideoFromFile.hpp"

namespace ie {
	VideoFromFile::Make::Make(std::vector<sf::Texture> video, MakeDyn<ISRFloat> viewing_progress) :
		video(std::move(video)), viewing_progress(std::move(viewing_progress)) {
	}
	
	VideoFromFile* VideoFromFile::Make::make(InitInfo init_info) {
		return new VideoFromFile{std::move(*this), init_info};
	}
	
	VideoFromFile::VideoFromFile(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		size_video_(make.video[0].getSize()),
		buffer_texture_(make.video),
		viewing_progress_(
			make.viewing_progress.make(init_info.dyn_buffer),
			[this](const float& value) {
				set_current_frame(value);
			}
		) {
		viewing_progress_.get().set_bounds(0., 1.);
		sprite_.setTexture(buffer_texture_[0]);
	}
	
	void VideoFromFile::set_current_frame(float viewing_progress) {
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
	
	void VideoFromFile::draw() {
		render_target_->draw(sprite_);
	}
	
	void VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size_ = size;
		sprite_.setPosition(position);
		sprite_.setScale(div_xy(size, sf::Vector2f{size_video_}));
	}
	
	sf::Vector2f VideoFromFile::get_area_position() const {
		return sprite_.getPosition();
	}
	
	sf::Vector2f VideoFromFile::get_area_size() const {
		return size_;
	}
	
	sf::Vector2f VideoFromFile::get_min_size() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromFile::get_normal_size() const {
		return sf::Vector2f{size_video_};
	}
}