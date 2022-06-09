#include "fullColor.h"

namespace ui {
    FullColor::FullColor(sf::Color color, sf::Vector2f normalSize) : IDrawn(), rectangle(), normalSize(normalSize) {
        rectangle.setFillColor(color);
    }

    void FullColor::draw() {
        window->draw(rectangle);
    }

    void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
        rectangle.setSize(size);
        rectangle.setPosition(position);
    }

    sf::Vector2f FullColor::getMinSize() {
        return {0, 0};
    }
	
	sf::Vector2f FullColor::getNormalSize(){
		return normalSize;
	}
}