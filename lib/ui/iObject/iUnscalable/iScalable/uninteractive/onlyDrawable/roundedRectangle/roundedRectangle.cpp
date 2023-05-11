#include "roundedRectangle.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius(radius) {
		horizontalRectangle.setFillColor(color);
		verticalRectangle.setFillColor(color);
		circle.setFillColor(color);
		circle.setRadius(radius);
	}
	
	void RoundedRectangle::draw() {
		renderTarget->draw(horizontalRectangle);
		renderTarget->draw(verticalRectangle);
		circle.setPosition(position);
		renderTarget->draw(circle);
		circle.setPosition(position.x + size.x - radius * 2, position.y);
		renderTarget->draw(circle);
		circle.setPosition(position.x, position.y + size.y - radius * 2);
		renderTarget->draw(circle);
		circle.setPosition(position.x + size.x - radius * 2, position.y + size.y - radius * 2);
		renderTarget->draw(circle);
	}
	
	void RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
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
		RoundedRectangle* rectangle{new RoundedRectangle{circle.getFillColor(), radius}};
		OnlyDrawable::copy(rectangle);
		Layout::copy(rectangle);
		rectangle->resize(size, position);
		return rectangle;
	}
	
	
	bool DecodePointer<RoundedRectangle>::decodePointer(const YAML::Node& node, RoundedRectangle*& roundedRectangle) {
		roundedRectangle = new RoundedRectangle{node["color"].as<sf::Color>(), node["radius"].as<float>()};
		return true;
	}
	
	template<>
	bool determine<RoundedRectangle>(const YAML::Node& node) {
		return determine(node, {{"color",  YAML::NodeType::Scalar},
								{"radius", YAML::NodeType::Scalar}});
	}
}
