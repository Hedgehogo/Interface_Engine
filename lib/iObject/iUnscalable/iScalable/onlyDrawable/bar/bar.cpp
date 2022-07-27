#include <cmath>
#include "bar.h"

void ui::Bar::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
	background->init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
	strip->init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
}

ui::Bar::Bar(OnlyDrawable *background, OnlyDrawable *strip, float offset, bool horizontal) :
	LayoutWithBackground(background), strip(strip), horizontal(horizontal), offset(offset), division(1.0f), value(0) {}

ui::Bar::Bar(OnlyDrawable *background, OnlyDrawable *strip, int division, float offset, bool horizontal) :
	LayoutWithBackground(background), strip(strip), horizontal(horizontal), offset(offset), division(division), value(0) {}

ui::Bar::~Bar() {
	delete strip;
}

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

void ui::Bar::draw() {}

void ui::Bar::resize(sf::Vector2f size, sf::Vector2f position) {
	LayoutWithBackground::resize(size, position);
	setValue(value);
}

sf::Vector2f ui::Bar::getMinSize() {
	sf::Vector2f stripMinSize{strip->getMinSize()};
	(horizontal ? stripMinSize.x : stripMinSize.y) *= value;
	return max(stripMinSize, background->getMinSize());
}

sf::Vector2f ui::Bar::getNormalSize() {
	sf::Vector2f stripNormalSize{strip->getNormalSize()};
	(horizontal ? stripNormalSize.x : stripNormalSize.y) *= value;
	return max(stripNormalSize, background->getNormalSize());
}

void ui::Bar::copy(ui::Bar *bar) {
	OnlyDrawable::copy(bar);
	Layout::copy(bar);
	bar->value = this->value;
}

ui::Bar *ui::Bar::copy() {
	Bar* bar {new Bar{background->copy(), strip->copy(), division, offset, horizontal}};
	Bar::copy(bar);
	return bar;
}

void ui::Bar::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    strip->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue, hueOffset);
}
