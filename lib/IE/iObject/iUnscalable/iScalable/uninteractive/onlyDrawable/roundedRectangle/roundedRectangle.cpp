#include "roundedRectangle.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	RoundedRectangle::Make::Make(sf::Color color, float radius) : color(color), radius(radius) {
	}
	
	RoundedRectangle* RoundedRectangle::Make::make(InitInfo initInfo) {
		return new RoundedRectangle{std::move(*this), initInfo};
	}
	
	RoundedRectangle::RoundedRectangle(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo), radius(make.radius) {
		horizontalRectangle.setFillColor(make.color);
		verticalRectangle.setFillColor(make.color);
		circle.setFillColor(make.color);
		circle.setRadius(radius);
	}
	
	RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius(radius) {
		horizontalRectangle.setFillColor(color);
		verticalRectangle.setFillColor(color);
		circle.setFillColor(color);
		circle.setRadius(radius);
	}
	
	void RoundedRectangle::draw() {
		renderTarget->draw(horizontalRectangle);
		renderTarget->draw(verticalRectangle);
		circle.setPosition(layout.position);
		renderTarget->draw(circle);
		circle.setPosition(layout.position.x + layout.size.x - radius * 2, layout.position.y);
		renderTarget->draw(circle);
		circle.setPosition(layout.position.x, layout.position.y + layout.size.y - radius * 2);
		renderTarget->draw(circle);
		circle.setPosition(layout.position.x + layout.size.x - radius * 2, layout.position.y + layout.size.y - radius * 2);
		renderTarget->draw(circle);
	}
	
	void RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		verticalRectangle.setSize({size.x - radius * 2, size.y});
		verticalRectangle.setPosition(position + sf::Vector2f{radius, 0});
		horizontalRectangle.setSize({size.x, size.y - radius * 2});
		horizontalRectangle.setPosition(position + sf::Vector2f{0, radius});
	}
	
	sf::Vector2f RoundedRectangle::getMinSize() const {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	sf::Vector2f RoundedRectangle::getNormalSize() const {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	RoundedRectangle* RoundedRectangle::copy() {
		return new RoundedRectangle{*this};
	}
	
	LayoutData& RoundedRectangle::layoutGetData() {
		return layout;
	}
	
	const LayoutData& RoundedRectangle::layoutGetData() const {
		return layout;
	}
	
	bool DecodePointer<RoundedRectangle>::decodePointer(const YAML::Node& node, RoundedRectangle*& roundedRectangle) {
		roundedRectangle = new RoundedRectangle{node["color"].as<sf::Color>(), node["radius"].as<float>()};
		return true;
	}
	
	template<>
	bool determine<RoundedRectangle>(const YAML::Node& node) {
		return determine(node, {
			{"color",  YAML::NodeType::Scalar},
			{"radius", YAML::NodeType::Scalar}
		});
	}
}
