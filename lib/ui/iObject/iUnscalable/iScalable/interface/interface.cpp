#include "interface.hpp"


namespace ui {
	void Interface::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &, InteractionStack &, IPanelManager &) {
		if(!initialized) {
			this->renderTarget = &renderTarget;
			drawManager.add(*this);
			updateManager.add(*this);
			object->init(renderTarget, this->drawManager, this->updateManager, this->interactionManager, *this->interactionStack, this->panelManager);
			initialized = true;
		}
	}
	
	void Interface::init(sf::RenderTarget &renderTarget) {
		if(!initialized) {
			this->renderTarget = &renderTarget;
			object->init(renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManager);
            sf::Vector2f size (max(static_cast<sf::Vector2f>(renderTarget.getSize()), object->getMinSize()));
			resize(size,sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	Interface::Interface(IScalable *object, AnimationManager animationManager, InteractionStack *interactionStack) :
		object(object), animationManager(std::move(animationManager)), interactionStack(interactionStack), renderTarget(nullptr), interactionManager(), panelManager(), initialized(false), active(true) {}
	
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
		interactionManager.update(sf::Vector2i(mousePosition));
	}

	void Interface::update() {
		animationManager.update();
		panelManager.update();
		updateManager.update();
		updateCluster(mousePosition);
		active = false;
	}
	
	void Interface::update(sf::Vector2f mousePosition, bool active) {
		if(active) {
			this->updateInteractions(mousePosition);
		} else {
			this->mousePosition = mousePosition;
		}
		this->update();
	}
	
	bool Interface::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		this->mousePosition = mousePosition;
		if(isInWindow(mousePosition) && !interactionManager.isBlocked()) {
			if(!panelManager.updateInteractions(mousePosition, true)) {
				object->updateInteractions(mousePosition);
			}
		}
		return true;
	}

	Interface *Interface::copy() {
		Interface* interface {new Interface{object->copy(), *animationManager.copy(), interactionStack}};
		interface->init(*renderTarget);
		return interface;
	}
	
	void Interface::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}

	sf::RenderTarget *Interface::getRenderTarget() {
		return renderTarget;
	}

	DrawManager *Interface::getDrawManager() {
		return &drawManager;
	}

	UpdateManager *Interface::getUpdateManager() {
		return &updateManager;
	}

	InteractionManager *Interface::getInteractionManager() {
		return &interactionManager;
	}

	InteractionStack *Interface::getInteractionStack() {
		return interactionStack;
	}

	PanelManager *Interface::getPanelManager() {
		return &panelManager;
	}

	IScalable *Interface::getObject() {
		return object;
	}

	bool convertPointer(const YAML::Node &node, Interface*& interface){
		interface = new Interface{
			node["object"].as<IScalable*>(),
			convDef(node["animation-manager"], AnimationManager{}),
			convDef(node["interaction-stack"], new InteractionStack{}),
		};
		return true;
	}
}
