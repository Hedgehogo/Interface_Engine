#include "interface.h"
#include <utility>

namespace ui {
	void Interface::init(sf::RenderWindow&, InteractionStack&, InteractionManager&, Panel *parent, PanelManager&) {
		if(!initialized) {
			initObject(object, this->window, this->interactionStack, this->interactionManager, parent, this->panelManager);
			initialized = true;
		}
	}
	
	void Interface::init() {
		if(!initialized) {
			initObject(object, window, interactionStack, interactionManager, nullptr, panelManager);
			resize(static_cast<sf::Vector2f>(window.getSize()), sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	Interface::Interface(IFlat* object, InteractionStack interactionStack, sf::RenderWindow &window) :
		object(object), interactionStack(std::move(interactionStack)), window(window), interactionManager(window), panelManager(), initialized(false) {}
	
	Interface::~Interface() {
		delete object;
	}
	
	bool Interface::isInWindow(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(window.getSize().x) && position.y > 0 && position.y < static_cast<float>(window.getSize().y);
	}
	
	void Interface::draw() {
		object->draw();
		panelManager.draw();
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
	
	void Interface::updateCluster(sf::Vector2f mousePosition) {
		interactionManager.update(static_cast<sf::Vector2i>(mousePosition));
	}
	
	void Interface::update() {
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if(isInWindow(mousePosition) && !interactionManager.isBlocked()) {
			panelManager.updateInteractions(mousePosition);
			object->updateInteractions(mousePosition);
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
}
