#include "interface.h"
#include "../../../../drawable/manager/drawManager.h"
#include <utility>
#include <iostream>

namespace ui {
	void Interface::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &, InteractionStack &, PanelManager &) {
		if(!initialized) {
			this->renderTarget = &renderTarget;
			object->init(renderTarget, this->drawManager, this->interactionManager, *this->interactionStack, this->panelManager);
			initialized = true;
		}
	}
	
	void Interface::init() {
		if(!initialized) {
            sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
			object->init(window, drawManager, interactionManager, *interactionStack, panelManager);
            sf::Vector2f minSize = object->getMinSize();
            sf::Vector2f size (std::max(windowSize.x,minSize.x), std::max(windowSize.y,minSize.y));
			window.setSize(static_cast<sf::Vector2u>(size));
			resize(size,sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	Interface::Interface(IScalable* object, InteractionStack *interactionStack, sf::RenderWindow &window) :
		object(object), interactionStack(interactionStack), renderTarget(&window), window(window), interactionManager(), panelManager(), initialized(false) {}
	
	Interface::~Interface() {
		delete object;
	}
	
	bool Interface::isInWindow(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(renderTarget->getSize().x) && position.y > 0 && position.y < static_cast<float>(renderTarget->getSize().y);
	}
	
	void Interface::draw() {
		drawManager.draw();
		panelManager.draw();
	}
	
	void Interface::resize(sf::Vector2f size, sf::Vector2f position) {
		object->resize(size, position);
	}
	
	bool Interface::updateInteractions(sf::Vector2f) {
		return false;
	}
	
	sf::Vector2f Interface::getAreaPosition() {
		return object->getAreaPosition();
	}
	
	sf::Vector2f Interface::getAreaSize() {
		return object->getAreaSize();
	}
	
	sf::Vector2f Interface::getMinSize() {
		return object->getMinSize();
	}
	
	sf::Vector2f Interface::getNormalSize() {
		return object->getNormalSize();
	}
	
	void Interface::updateCluster(sf::Vector2f mousePosition) {
		interactionManager.update(static_cast<sf::Vector2i>(mousePosition));
	}
	
	void Interface::update() {
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if(isInWindow(mousePosition) && window.getSystemHandle() && !interactionManager.isBlocked()) {
			if(!panelManager.updateInteractions(mousePosition, true)) {
				object->updateInteractions(mousePosition);
			}
		}
		panelManager.update();
		object->update();
		updateCluster(mousePosition);
	}
	
	void Interface::update(int wheel) {
		sf::Wheel::value = wheel;
		update();
	}
	
	Interface *Interface::copy() {
		Interface* interface {new Interface{object->copy(), interactionStack, window}};
		interface->init();
		return interface;
	}
	
	void Interface::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}
