#include "fullColor.h"

namespace ui {
    FullColor::FullColor(sf::Color color, sf::Vector2f normalSize) : OnlyDrawable(), rectangle(), normalSize(normalSize) {
        rectangle.setFillColor(color);
    }

    void FullColor::draw() {
        renderTarget->draw(rectangle);
    }

    void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
        rectangle.setSize(size);
        rectangle.setPosition(position);
    }
	
	sf::Vector2f FullColor::getAreaPosition() {
		return rectangle.getPosition();
	}
	
	sf::Vector2f FullColor::getAreaSize() {
		return rectangle.getSize();
	}

    sf::Vector2f FullColor::getMinSize() {
        return sf::Vector2f();
    }
	
	sf::Vector2f FullColor::getNormalSize(){
		return normalSize;
	}
	
	FullColor *FullColor::copy() {
		FullColor* fullColor {new FullColor{rectangle.getFillColor(), normalSize}};
		OnlyDrawable::copy(fullColor);
		return fullColor;
	}
}