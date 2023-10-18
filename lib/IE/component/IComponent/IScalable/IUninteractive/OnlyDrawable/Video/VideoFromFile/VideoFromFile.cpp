#include "VideoFromFile.hpp"

namespace ie {
	VideoFromFile::Make::Make(std::vector<sf::Texture> video, PSCoefficient viewing_progress) :
		video(std::move(video)), viewing_progress(viewing_progress) {
	}
	
	VideoFromFile* VideoFromFile::Make::make(InitInfo init_info) {
		return new VideoFromFile{std::move(*this), init_info};
	}
	
	VideoFromFile::VideoFromFile(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		size_video(make.video[0].getSize()),
		buffer_texture(make.video),
		viewing_progress(make.viewing_progress) {
		viewing_progress->add_setter([=](float value) {
			set_current_frame(value);
		});
		sprite.setTexture(buffer_texture[0]);
	}
	
	VideoFromFile::VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewing_progress) :
		size_video(video[0].getSize()), buffer_texture(video), viewing_progress(viewing_progress) {
		viewing_progress->add_setter([=](float viewing_progress) {
			set_current_frame(viewing_progress);
		});
		sprite.setTexture(buffer_texture[0]);
	}
	
	void VideoFromFile::set_current_frame(float viewing_progress) {
		if(viewing_progress >= 1) {
			sprite.setTexture(buffer_texture[buffer_texture.size()]);
			return;
		}
		if(viewing_progress <= 0) {
			sprite.setTexture(buffer_texture[0]);
			return;
		}
		sprite.setTexture(buffer_texture[buffer_texture.size() * viewing_progress]);
	}
	
	void VideoFromFile::draw() {
		render_target->draw(sprite);
	}
	
	void VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		sprite.setPosition(position);
		sprite.setScale(size / sf::Vector2f{size_video});
	}
	
	sf::Vector2f VideoFromFile::get_area_position() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f VideoFromFile::get_area_size() const {
		return size;
	}
	
	sf::Vector2f VideoFromFile::get_min_size() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromFile::get_normal_size() const {
		return sf::Vector2f{size_video};
	}
	
	VideoFromFile* VideoFromFile::copy() {
		return new VideoFromFile{*this};
	}
}