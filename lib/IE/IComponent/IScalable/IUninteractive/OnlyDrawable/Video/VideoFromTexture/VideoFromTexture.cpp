#include "VideoFromTexture.hpp"

namespace ie {
	VideoFromTexture::Make::Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, std::size_t frameCount, sf::Vector2i offset) :
		texture(texture), viewingProgress(viewingProgress), rect(rect), frameCount(frameCount), offset(offset) {
	}
	
	VideoFromTexture::Make::Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, std::size_t frameCount) :
		texture(texture), viewingProgress(viewingProgress), rect(rect), frameCount(frameCount), offset(this->rect.width, 0) {
	}
	
	VideoFromTexture::Make::Make(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect) :
		texture(texture),
		viewingProgress(viewingProgress),
		rect(rect),
		frameCount(this->texture.getSize().x / this->rect.width),
		offset(this->rect.width, 0) {
	}
	
	VideoFromTexture* VideoFromTexture::Make::make(InitInfo initInfo) {
		return new VideoFromTexture{std::move(*this), initInfo};
	}
	
	VideoFromTexture::VideoFromTexture(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo),
		rect(make.rect),
		offset(make.offset),
		viewingProgress(make.viewingProgress),
		sprite(make.texture, make.rect),
		textureSize(make.texture.getSize()),
		frameCount(make.frameCount) {
		viewingProgress->addSetter([=](float value) {
			setCurrentFrame(value);
		});
	}
	
	VideoFromTexture::VideoFromTexture(const sf::Texture& texture, PSCoefficient viewingProgress, sf::IntRect rect, std::size_t frameCount, sf::Vector2i offset) :
		rect(rect), offset(offset), viewingProgress(viewingProgress), textureSize(texture.getSize()), frameCount(frameCount) {
		viewingProgress->addSetter([=](float viewingProgress) {
			setCurrentFrame(viewingProgress);
		});
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		
		if(rect.height == 0) {
			this->rect.height = textureSize.y - rect.top;
		}
		if(rect.width == 0) {
			this->rect.width = this->rect.height;
		}
		
		if(frameCount == 0) {
			this->frameCount = this->textureSize.x / this->rect.width;
		}
		
		if(offset.x == 0 && offset.y == 0) {
			this->offset.x = this->rect.width;
		}
	}
	
	void VideoFromTexture::setCurrentFrame(float viewingProgress) {
		sprite.setTextureRect({(offset * static_cast<int>(viewingProgress * frameCount)) + sf::Vector2i{rect.left, rect.top}, {rect.width, rect.height}});
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
		return new VideoFromTexture{*this};
	}
}