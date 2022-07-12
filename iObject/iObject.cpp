#include <cmath>
#include "iObject.h"

void ui::IObject::initObject(IObject *object, sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	if(object != nullptr) {
		object->init(renderTarget, interactionStack, interactionManager, panelManager);
	}
}

void ui::IObject::setPosition(sf::Vector2f position) {
	resize(getAreaSize(), position);
}

void ui::IObject::move(sf::Vector2f position) {
	resize(getAreaSize(), getPosition() + position);
}

void ui::IObject::setSize(sf::Vector2f size) {
	resize(size, getPosition());
}

sf::Vector2f ui::IObject::getSize() {
	return getAreaSize();
}

void ui::IObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent, indent} * 2)};
	sf::Vector2f position{this->getPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
    if (size.x > 0 && size.y > 0){
        sf::RectangleShape rectangle;
        rectangle.setFillColor(HSVtoRGB(hue % 360));

        rectangle.setPosition(position);
        rectangle.setSize({1.0f, size.y});
        renderTarget.draw(rectangle);

        rectangle.setPosition({position.x + size.x - 1.0f, position.y});
        renderTarget.draw(rectangle);

        rectangle.setPosition(position);
        rectangle.setSize({size.x, 1.0f});
        renderTarget.draw(rectangle);

        rectangle.setPosition({position.x, position.y + size.y - 1.0f});
        renderTarget.draw(rectangle);
    }
}

sf::Color ui::IObject::HSVtoRGB(float H, float S, float V)
{
    float C = S * V; // Chroma
    float HPrime = std::fmod(H / 60, 6.f); // H'
    float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
    float M = V - C;

    float R = 0.f;
    float G = 0.f;
    float B = 0.f;

    switch (static_cast<int>(HPrime))
    {
        case 0: R = C; G = X;        break; // [0, 1)
        case 1: R = X; G = C;        break; // [1, 2)
        case 2:        G = C; B = X; break; // [2, 3)
        case 3:        G = X; B = C; break; // [3, 4)
        case 4: R = X;        B = C; break; // [4, 5)
        case 5: R = C;        B = X; break; // [5, 6)
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