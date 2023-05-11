#include "layoutWithBackground.hpp"

namespace ui {
	LayoutWithBackground::LayoutWithBackground(IUninteractive* background) : background(background) {
	}
	
	void LayoutWithBackground::init(InitInfo initInfo) {
		background->init(initInfo);
	}
	
	LayoutWithBackground::~LayoutWithBackground() {
		delete background;
	}
	
	void LayoutWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		background->resize(size, position);
	}
	
	sf::Vector2f LayoutWithBackground::getMinSize() const {
		return background->getMinSize();
	}
	
	sf::Vector2f LayoutWithBackground::getNormalSize() const {
		return background->getNormalSize();
	}
	
	void LayoutWithBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}