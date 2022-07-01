#include <cmath>
#include "bar.h"

void ui::Bar::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	initObject(background, renderTarget, interactionStack, interactionManager, panelManager);
	initObject(strip, renderTarget, interactionStack, interactionManager, panelManager);
}

ui::Bar::Bar(IDrawn *background, IDrawn *strip, float offset, bool horizontal) :
	background(background), strip(strip), horizontal(horizontal), offset(offset), division(1.0f), value(0) {}

ui::Bar::Bar(IDrawn *background, IDrawn *strip, int division, float offset, bool horizontal) :
	background(background), strip(strip), horizontal(horizontal), offset(offset), division(division), value(0) {}

float ui::Bar::getValue() {
	return value;
}

void ui::Bar::setValue(float value) {
	this->value = value;
	if(this->division > 1) {
		this->value = std::round(this->value);
	}
	sf::Vector2f stripSize{size};
	if(horizontal) {
		stripSize.x = offset * size.y;
		stripSize.x += (size.x - stripSize.x) * this->value / static_cast<float>(division);
	} else {
		stripSize.y = offset * size.x;
		stripSize.y += (size.y - stripSize.y) * this->value / static_cast<float>(division);
	}
	strip->resize(stripSize, position);
}

void ui::Bar::draw() {
	background->draw();
	strip->draw();
}

void ui::Bar::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
	background->resize(size, position);
	setValue(value);
}

sf::Vector2f ui::Bar::getMinSize() {
	return strip->getMinSize();
}

sf::Vector2f ui::Bar::getNormalSize() {
	return strip->getNormalSize();
}

ui::Bar *ui::Bar::copy() {
	Bar* bar {new Bar{background->copy(), strip->copy(), division, offset, horizontal}};
	IDrawn::copy(bar);
	Layout::copy(bar);
	bar->value = this->value;
	bar->resize(size, position);
	return bar;
}
