#include "iObject.hpp"
#include "../../modules/appendix/hsvToRgb/hsvToRgb.hpp"

namespace ui {
	void IObject::setPosition(sf::Vector2f position) {
		resize(getAreaSize(), position);
	}
	
	void IObject::move(sf::Vector2f position) {
		resize(getAreaSize(), getAreaPosition() + position);
	}
	
	void IObject::setSize(sf::Vector2f size) {
		resize(size, getAreaPosition());
	}
	
	sf::Vector2f IObject::getPosition() const {
		return getAreaPosition();
	}
	
	sf::Vector2f IObject::getSize() const {
		return getAreaSize();
	}
	
	bool IObject::inArea(sf::Vector2f pointPosition) {
		sf::Vector2f size{getAreaSize()};
		sf::Vector2f position{getAreaPosition()};
		return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
			   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
	}
	
	bool IObject::in(sf::Vector2f pointPosition) {
		return inArea(pointPosition);
	}
	
	void IObject::drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& renderTarget, uint hue) {
		if(size.x > 0 && size.y > 0) {
			sf::Color color{hsvToRgb(static_cast<float>(hue % 360))};
			
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(color);
			
			renderTarget.draw(rectangle);
			
			sf::CircleShape circle{2, 4};
			circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
			circle.setFillColor(color);
			
			renderTarget.draw(circle);
		}
	}
	
	void IObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int, uint hue, uint) {
		sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2 + 2, indent * 2 + 2})};
		sf::Vector2f position{this->getAreaPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent + 1, indent + 1})};
		if(size.x > 0 && size.y > 0) {
			sf::Color color{hsvToRgb(static_cast<float>(hue % 360))};
			
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(color);
			
			renderTarget.draw(rectangle);
			
			sf::CircleShape circle{2, 4};
			circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
			circle.setFillColor(color);
			
			renderTarget.draw(circle);
		}
	}
}