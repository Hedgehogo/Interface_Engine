#include <cmath>
#include "iObject.hpp"

namespace ui {
	void IObject::setPosition(sf::Vector2f position) {
		resize(getAreaSize(), position);
	}
	
	sf::Vector2f IObject::getPosition() {
		return getAreaPosition();
	}
	
	void IObject::move(sf::Vector2f position) {
		resize(getAreaSize(), getAreaPosition() + position);
	}
	
	void IObject::setSize(sf::Vector2f size) {
		resize(size, getAreaPosition());
	}
	
	sf::Vector2f IObject::getSize() {
		return getAreaSize();
	}
	
	bool IObject::inArea(sf::Vector2f pointPosition) {
		sf::Vector2f size{getAreaSize()};
		sf::Vector2f position{getAreaPosition()};
		return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
			   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
	}
	
	bool IObject::in(sf::Vector2f pointPosition) {
		sf::Vector2f size{getSize()};
		sf::Vector2f position{getPosition()};
		return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
			   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
	}
	
	void IObject::drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget &renderTarget, uint hue) {
		if(size.x > 0 && size.y > 0) {
			sf::Color color{HSVtoRGB(static_cast<float>(hue % 360))};
			
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
	
	void IObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int, uint hue, uint) {
		sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2 + 2, indent * 2 + 2})};
		sf::Vector2f position{this->getAreaPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent + 1, indent + 1})};
		if(size.x > 0 && size.y > 0) {
			sf::Color color{HSVtoRGB(static_cast<float>(hue % 360))};
			
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
	
	sf::Color IObject::HSVtoRGB(float H, float S, float V) {
		float C = S * V; // Chroma
		float HPrime = std::fmod(H / 60, 6.f); // H'
		float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
		float M = V - C;
		
		float R = 0.f;
		float G = 0.f;
		float B = 0.f;
		
		switch(static_cast<int>(HPrime)) {
			case 0:
				R = C;
				G = X;
				break; // [0, 1)
			case 1:
				R = X;
				G = C;
				break; // [1, 2)
			case 2:
				G = C;
				B = X;
				break; // [2, 3)
			case 3:
				G = X;
				B = C;
				break; // [3, 4)
			case 4:
				R = X;
				B = C;
				break; // [4, 5)
			case 5:
				R = C;
				B = X;
				break; // [5, 6)
		}
		
		R += M;
		G += M;
		B += M;
		
		sf::Color color;
		color.r = static_cast<sf::Uint8>(std::round(R * 255));
		color.g = static_cast<sf::Uint8>(std::round(G * 255));
		color.b = static_cast<sf::Uint8>(std::round(B * 255));
		
		return color;
	}
}