#include "interface.h"
#include <utility>

namespace ui {
	void Interface::init(sf::RenderWindow&, InteractionStack&, InteractionManager&, Panel *parent, PanelManager&) {
		if(!initialized) {
			initObject(object, this->window, this->interactionStack, this->interactionManager, parent, this->panelStack);
			initialized = true;
		}
	}
	
	void Interface::init() {
		if(!initialized) {
			initObject(object, window, interactionStack, interactionManager, nullptr, panelStack);
			resize(static_cast<sf::Vector2f>(window.getSize()), sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	Interface::Interface(IFlat* object, InteractionStack interactionStack, sf::RenderWindow &window) :
		object(object), interactionStack(std::move(interactionStack)), window(window), interactionManager(window), panelStack(), initialized(false) {}
	
	Interface::~Interface() {
		delete object;
	}
	
	bool Interface::inWindow(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(window.getSize().x) && position.y > 0 && position.y < static_cast<float>(window.getSize().y);
	}
	
	void Interface::draw() {
		object->draw();
		panelStack.draw();
	}
	
	void Interface::resize(sf::Vector2f size, sf::Vector2f position) {
		object->resize(size, position);
	}
	
	bool Interface::updateInteractions(sf::Vector2f) {
		return false;
	}
	
	sf::Vector2f Interface::getMinSize() {
		return object->getMinSize();
	}
	
	sf::Vector2f Interface::getNormalSize() {
		return object->getNormalSize();
	}
	
	void Interface::updateCluster() {
		interactionManager.update();
	}
	
	void Interface::update() {
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(interactionManager.getPosition());
		if(inWindow(mousePosition) && !interactionManager.blocked()) {
			panelStack.updateInteractions(mousePosition);
			object->updateInteractions(mousePosition);
		}
		updateCluster();
		panelStack.update();
		object->update();
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
}
