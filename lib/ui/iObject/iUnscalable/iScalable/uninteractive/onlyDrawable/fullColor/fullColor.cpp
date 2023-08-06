#include "fullColor.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	FullColor::Make::Make(sf::Color color, sf::Vector2f normalSize) : color(color), normalSize(normalSize) {
	}
	
	FullColor* FullColor::Make::make(InitInfo initInfo) {
		return new FullColor{std::move(*this), initInfo};
	}
	
	FullColor::FullColor(FullColor::Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo), normalSize(make.normalSize) {
		rectangle.setFillColor(make.color);
	}
	
	FullColor::FullColor(sf::Color color, sf::Vector2f normalSize) : OnlyDrawable(), rectangle(), normalSize(normalSize) {
		rectangle.setFillColor(color);
	}
	
	void FullColor::draw() {
		renderTarget->draw(rectangle);
	}
	
	void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
		rectangle.setSize(size);
		rectangle.setPosition(position);
	}
	
	sf::Vector2f FullColor::getAreaPosition() const {
		return rectangle.getPosition();
	}
	
	sf::Vector2f FullColor::getAreaSize() const {
		return rectangle.getSize();
	}
	
	sf::Vector2f FullColor::getMinSize() const {
		return sf::Vector2f();
	}
	
	sf::Vector2f FullColor::getNormalSize() const {
		return normalSize;
	}
	
	FullColor* FullColor::copy() {
		return new FullColor{*this};
	}
	
	bool DecodePointer<FullColor>::decodePointer(const YAML::Node& node, FullColor*& fullColor) {
		if(node.IsScalar()) {
			fullColor = new FullColor{node.as<sf::Color>(), {}};
		} else {
			fullColor = new FullColor{
				node["color"].as<sf::Color>(),
				convDef(node["normal-size"], sf::Vector2f{})
			};
		}
		return true;
	}
	
	template<>
	bool determine<FullColor>(const YAML::Node& node) {
		if(node.IsScalar()) {
			return node.as<std::string>().size() <= 11;
		} else {
			return determine(node, {{"color", YAML::NodeType::Scalar}}, {{"normal-size"}});
		}
	}
}
