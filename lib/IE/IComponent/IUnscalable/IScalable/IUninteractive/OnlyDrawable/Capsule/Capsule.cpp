#include "Capsule.hpp"

namespace ui {
	Capsule::Make::Make(sf::Color color) : color(color) {
	}
	
	Capsule* Capsule::Make::make(InitInfo initInfo) {
		return new Capsule{std::move(*this), initInfo};
	}
	
	Capsule::Capsule(Make&& make, InitInfo initInfo) : OnlyDrawable(initInfo) {
		rectangle.setFillColor(make.color);
		circle.setFillColor(make.color);
	}
	
	Capsule::Capsule(sf::Color color) : ILayout() {
		rectangle.setFillColor(color);
		circle.setFillColor(color);
	}
	
	void Capsule::draw() {
		renderTarget->draw(rectangle);
		circle.setPosition(layout.position);
		renderTarget->draw(circle);
		if(layout.size.x > layout.size.y) {
			circle.setPosition({layout.position.x + layout.size.x - layout.size.y, layout.position.y});
		} else {
			circle.setPosition({layout.position.x, layout.position.y + layout.size.y - layout.size.x});
		}
		renderTarget->draw(circle);
	}
	
	void Capsule::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		if(size.x > size.y) {
			rectangle.setSize({size.x - size.y, size.y});
			rectangle.setPosition(position + sf::Vector2f{size.y / 2, 0});
			circle.setRadius(size.y / 2);
		} else {
			rectangle.setSize({size.x, size.y - size.x});
			rectangle.setPosition(position + sf::Vector2f{0, size.x / 2});
			circle.setRadius(size.x / 2);
		}
	}
	
	sf::Vector2f Capsule::getMinSize() const {
		return {0, 0};
	}
	
	sf::Vector2f Capsule::getNormalSize() const {
		return {1, 1};
	}
	
	Capsule* Capsule::copy() {
		return new Capsule{*this};
	}
	
	LayoutData& Capsule::layoutGetData() {
		return layout;
	}
	
	const LayoutData& Capsule::layoutGetData() const {
		return layout;
	}
	
	bool DecodePointer<Capsule>::decodePointer(const YAML::Node& node, Capsule*& capsule) {
		capsule = new Capsule{node["color"].as<sf::Color>()};
		return true;
	}
}
