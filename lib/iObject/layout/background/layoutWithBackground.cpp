#include "layoutWithBackground.h"

namespace ui {
	LayoutWithBackground::LayoutWithBackground(OnlyDrawable *background) : background(background) {}
	
	void LayoutWithBackground::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		background->init(renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayoutWithBackground::~LayoutWithBackground() {
		delete background;
	}
	
	void LayoutWithBackground::draw() {
		background->draw();
	}
	
	void LayoutWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		background->resize(size, position);
	}
	
	sf::Vector2f LayoutWithBackground::getMinSize() {
		return background->getMinSize();
	}
	
	sf::Vector2f LayoutWithBackground::getNormalSize() {
		return background->getNormalSize();
	}
	
	void LayoutWithBackground::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}