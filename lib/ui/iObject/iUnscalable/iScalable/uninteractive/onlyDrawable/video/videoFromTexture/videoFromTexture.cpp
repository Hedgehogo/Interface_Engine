#include "videoFromTexture.hpp"

namespace ui {
	VideoFromTexture::VideoFromTexture(sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, int countFrame, sf::Vector2i offset) :
		viewingProgress(viewingProgress), rect(rect), countFrame(countFrame), offset(offset), textureSize(texture.getSize()) {
		viewingProgress->addSetter([=](float viewingProgress) {
			setCurrentFrame(viewingProgress);
		});
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		
		if(rect.height == 0)
			this->rect.height = textureSize.y - rect.top;
		if(rect.width == 0)
			this->rect.width = this->rect.height;
		
		if(countFrame == 0)
			this->countFrame = this->textureSize.x / this->rect.width;
		
		if(offset.x == 0 && offset.y == 0) {
			this->offset.x = this->rect.width;
		}
	}
	
	void VideoFromTexture::setCurrentFrame(float viewingProgress) {
		sprite.setTextureRect({(offset * static_cast<int>(viewingProgress * countFrame)) + sf::Vector2i{rect.left, rect.top}, {rect.width, rect.height}});
	}
	
	void VideoFromTexture::draw() {
		renderTarget->draw(sprite);
	}
	
	sf::Vector2f VideoFromTexture::getAreaPosition() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f VideoFromTexture::getAreaSize() const {
		return size;
	}
	
	sf::Vector2f VideoFromTexture::getMinSize() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromTexture::getNormalSize() const {
		return sf::Vector2f{sf::Vector2i{rect.width, rect.height}};
	}
	
	void VideoFromTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		sprite.setPosition(position);
		sprite.setScale(size / sf::Vector2f{sf::Vector2i{rect.width, rect.height}});
	}
	
	VideoFromTexture* VideoFromTexture::copy() {
		return nullptr;
	}
}