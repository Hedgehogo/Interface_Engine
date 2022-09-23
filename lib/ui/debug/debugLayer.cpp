#include "debugLayer.hpp"
#include "../iObject/../drawable/manager/drawManager.hpp"
#include <cmath>

namespace ui {
	DebugLayer::DebugLayer(IScalable *object) :
		Layer({}), object(object), renderTarget(nullptr), active(false), drawn(false) {}
	
	void DebugLayer::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		object->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		drawManager.add(*this);
		this->renderTarget = &renderTarget;
	}
	
	DebugLayer::~DebugLayer() {
		delete object;
	}
	
	void DebugLayer::draw() {
		drawn = true;
		object->drawDebug(*renderTarget, 0, 2, 0, 72);
	}
	
	void DebugLayer::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		object->resize(size, position);
	}
	
	bool DebugLayer::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f DebugLayer::getMinSize() {
		return object->getMinSize();
	}
	
	sf::Vector2f DebugLayer::getNormalSize() {
		return object->getNormalSize();
	}
	
	DebugLayer *DebugLayer::copy() {
		DebugLayer* debugLayer{new DebugLayer{object->copy()}};
		return debugLayer;
	}
	
	void DebugLayer::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2, indent * 2})};
		size = {std::round(size.x - 2.0f), std::round(size.y - 2.0f)};
		sf::Vector2f position{this->getAreaPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
		position = {std::round(position.x + 1.0f), std::round(position.y + 1.0f)};
		
		if(drawn || active) {
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			
			if(drawn && active) {
				rectangle.setFillColor(sf::Color(0, 255, 0, 60));
			} else if (drawn) {
				rectangle.setFillColor(sf::Color(255, 255, 0, 60));
			} else if (active) {
				rectangle.setFillColor(sf::Color(255, 0, 0, 60));
			}
			
			renderTarget.draw(rectangle);
		}
		
		active = false;
		drawn = false;
		
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}