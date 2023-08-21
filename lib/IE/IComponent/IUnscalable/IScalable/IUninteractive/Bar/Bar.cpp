#include <cmath>
#include "Bar.hpp"

namespace ui {
	Bar::Make::Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(1) {
	}
	
	Bar::Make::Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, int division, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(division) {
	}
	
	Bar* Bar::Make::make(InitInfo initInfo) {
		return new Bar{std::move(*this), initInfo};
	}
	
	Bar::Bar(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo),
		background(make.background->make(initInfo)),
		strip(make.strip->make(initInfo)),
		horizontal(make.horizontal),
		offset(make.offset),
		division(make.division),
		value(0) {
	}
	
	Bar::Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), horizontal(horizontal), offset(offset), division(1), value(0) {
	}
	
	Bar::Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, int division, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), horizontal(horizontal), offset(offset), division(division), value(0) {
	}
	
	void Bar::init(InitInfo initInfo) {
		background->init(initInfo);
		strip->init(initInfo);
	}
	
	float Bar::getValue() {
		return value;
	}
	
	void Bar::setValue(float value) {
		this->value = value;
		if(this->division > 1) {
			this->value = std::round(this->value);
		}
		sf::Vector2f stripSize{layout.size};
		if(horizontal) {
			stripSize.x = offset * layout.size.y;
			stripSize.x += (layout.size.x - stripSize.x) * this->value / static_cast<float>(division);
		} else {
			stripSize.y = offset * layout.size.x;
			stripSize.y += (layout.size.y - stripSize.y) * this->value / static_cast<float>(division);
		}
		strip->resize(stripSize, layout.position);
	}
	
	void Bar::draw() {
	}
	
	void Bar::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutBackground::resize(size, position);
		setValue(value);
	}
	
	sf::Vector2f Bar::getMinSize() const {
		sf::Vector2f stripMinSize{strip->getMinSize()};
		(horizontal ? stripMinSize.x : stripMinSize.y) *= value;
		return max(stripMinSize, background->getMinSize());
	}
	
	sf::Vector2f Bar::getNormalSize() const {
		sf::Vector2f stripNormalSize{strip->getNormalSize()};
		(horizontal ? stripNormalSize.x : stripNormalSize.y) *= value;
		return max(stripNormalSize, background->getNormalSize());
	}
	
	IUninteractive& Bar::getBackground() {
		return *background;
	}
	
	const IUninteractive& Bar::getBackground() const {
		return *background;
	}
	
	Bar* Bar::copy() {
		return new Bar{*this};
	}
	
	void Bar::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		strip->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue, hueOffset);
	}
	
	LayoutData& Bar::layoutGetData() {
		return layout;
	}
	
	const LayoutData& Bar::layoutGetData() const {
		return layout;
	}
	
	bool DecodePointer<Bar>::decodePointer(const YAML::Node& node, Bar*& bar) {
		bar = new Bar{
			node["background"].as<BoxPtr<IUninteractive> >(),
			node["strip"].as<BoxPtr<IUninteractive> >(),
			convDef(node["division"], 1),
			convDef(node["offset"], 0.0f),
			convDef(node["offset"], true)
		};
		return true;
	}
}
