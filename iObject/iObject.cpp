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

void ui::IObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition) {
	sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent, indent} * 2)};
	sf::Vector2f position{this->getPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Blue);
	
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
