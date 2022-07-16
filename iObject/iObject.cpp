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

sf::Vector2f ui::IObject::getPosition() {
	return getAreaPosition();
}

void ui::IObject::move(sf::Vector2f position) {
	resize(getAreaSize(), getAreaPosition() + position);
}

void ui::IObject::setSize(sf::Vector2f size) {
	resize(size, getAreaPosition());
}

sf::Vector2f ui::IObject::getSize() {
	return getAreaSize();
}

bool ui::IObject::inArea(sf::Vector2f pointPosition) {
	sf::Vector2f size {getAreaSize()};
	sf::Vector2f position {getAreaPosition()};
	return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
		   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
}

bool ui::IObject::in(sf::Vector2f pointPosition) {
	sf::Vector2f size {getSize()};
	sf::Vector2f position {getPosition()};
	return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
		   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
}

void ui::IObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int, uint hue, uint) {
	sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2, indent * 2})};
	size = {std::round(size.x - 1.0f), std::round(size.y - 1.0f)};
	sf::Vector2f position{this->getAreaPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
	position = {std::round(position.x + 1.0f), std::round(position.y)};
    if (size.x > 0 && size.y > 0){
		sf::Color color{HSVtoRGB(static_cast<float>(hue % 360))};
		sf::Vertex frame[] {
			{position, color},
			{{position.x + size.x, position.y}, color},
			{position + size, color},
			{{position.x, position.y + size.y}, color},
			{position, color},
		};
		
		sf::CircleShape circle{2, 4};
		circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
		circle.setFillColor(color);
		
		renderTarget.draw(frame, 5, sf::LinesStrip);
		
		renderTarget.draw(circle);
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
