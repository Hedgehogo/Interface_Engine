#include "VideoFromFile.hpp"

namespace ie {
	VideoFromFile::Make::Make(std::vector<sf::Texture> video, PSCoefficient viewingProgress) :
		video(std::move(video)), viewingProgress(viewingProgress) {
	}
	
	VideoFromFile* VideoFromFile::Make::make(InitInfo initInfo) {
		return new VideoFromFile{std::move(*this), initInfo};
	}
	
	VideoFromFile::VideoFromFile(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo),
		sizeVideo(make.video[0].getSize()),
		bufferTexture(make.video),
		viewingProgress(make.viewingProgress) {
		viewingProgress->addSetter([=](float value) {
			setCurrentFrame(value);
		});
		sprite.setTexture(bufferTexture[0]);
	}
	
	VideoFromFile::VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewingProgress) :
		sizeVideo(video[0].getSize()), bufferTexture(video), viewingProgress(viewingProgress) {
		viewingProgress->addSetter([=](float viewingProgress) {
			setCurrentFrame(viewingProgress);
		});
		sprite.setTexture(bufferTexture[0]);
	}
	
	void VideoFromFile::setCurrentFrame(float viewingProgress) {
		if(viewingProgress >= 1) {
			sprite.setTexture(bufferTexture[bufferTexture.size()]);
			return;
		}
		if(viewingProgress <= 0) {
			sprite.setTexture(bufferTexture[0]);
			return;
		}
		sprite.setTexture(bufferTexture[bufferTexture.size() * viewingProgress]);
	}
	
	void VideoFromFile::draw() {
		renderTarget->draw(sprite);
	}
	
	void VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		sprite.setPosition(position);
		sprite.setScale(size / sf::Vector2f{sizeVideo});
	}
	
	sf::Vector2f VideoFromFile::getAreaPosition() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f VideoFromFile::getAreaSize() const {
		return size;
	}
	
	sf::Vector2f VideoFromFile::getMinSize() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromFile::getNormalSize() const {
		return sf::Vector2f{sizeVideo};
	}
	
	VideoFromFile* VideoFromFile::copy() {
		return new VideoFromFile{*this};
	}
}