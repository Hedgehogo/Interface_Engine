#include <cmath>
#include "bar.hpp"

namespace ui {
	void Bar::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		background->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		strip->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	Bar::Bar(IUninteractive *background, IUninteractive *strip, float offset, bool horizontal) :
		LayoutWithBackground(background), strip(strip), horizontal(horizontal), offset(offset), division(1), value(0) {
	}
	
	Bar::Bar(IUninteractive *background, IUninteractive *strip, int division, float offset, bool horizontal) :
		LayoutWithBackground(background), strip(strip), horizontal(horizontal), offset(offset), division(division), value(0) {
	}
	
	Bar::~Bar() {
		delete strip;
	}
	
	float Bar::getValue() {
		return value;
	}
	
	void Bar::setValue(float value) {
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
	
	void Bar::draw() {
	}
	
	void Bar::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithBackground::resize(size, position);
		setValue(value);
	}
	
	sf::Vector2f Bar::getMinSize() {
		sf::Vector2f stripMinSize{strip->getMinSize()};
		(horizontal ? stripMinSize.x : stripMinSize.y) *= value;
		return max(stripMinSize, background->getMinSize());
	}
	
	sf::Vector2f Bar::getNormalSize() {
		sf::Vector2f stripNormalSize{strip->getNormalSize()};
		(horizontal ? stripNormalSize.x : stripNormalSize.y) *= value;
		return max(stripNormalSize, background->getNormalSize());
	}
	
	void Bar::copy(Bar *bar) {
		OnlyDrawable::copy(bar);
		Layout::copy(bar);
		bar->value = this->value;
	}
	
	Bar *Bar::copy() {
		Bar *bar{new Bar{background->copy(), strip->copy(), division, offset, horizontal}};
		Bar::copy(bar);
		return bar;
	}
	
	void Bar::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		strip->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, Bar *&bar) {
		IUninteractive *background;
		IUninteractive *strip;
		int division{1};
		float offset{0.0f};
		bool horizontal{true};
		
		node["background"] >> background;
		node["strip"] >> strip;
		if(node["division"])
			node["division"] >> division;
		if(node["offset"])
			node["offset"] >> offset;
		if(node["horizontal"])
			node["horizontal"] >> horizontal;
		
		{ bar = new Bar{background, strip, division, offset, horizontal}; return true; }
	}
}
