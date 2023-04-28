#include "boxDebug.hpp"
#include <cmath>

namespace ui {
	BoxDebug::BoxDebug(IScalable *object) :
		Box({}), object(object), renderTarget(nullptr), active(false), drawn(false) {}
	
	void BoxDebug::init(InitInfo initInfo) {
		object->init(initInfo);
		initInfo.drawManager.add(*this);
		this->renderTarget = &initInfo.renderTarget;
	}
	
	BoxDebug::~BoxDebug() {
		delete object;
	}
	
	void BoxDebug::draw() {
		drawn = true;
		object->drawDebug(*renderTarget, 0, 2, 0, 72);
	}
	
	void BoxDebug::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		object->resize(size, position);
	}
	
	bool BoxDebug::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxDebug::getMinSize() {
		return object->getMinSize();
	}
	
	sf::Vector2f BoxDebug::getNormalSize() {
		return object->getNormalSize();
	}
	
	BoxDebug *BoxDebug::copy() {
		BoxDebug* boxDebug{new BoxDebug{object->copy()}};
		return boxDebug;
	}
	
	void BoxDebug::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		sf::Vector2f size{this->getAreaSize() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2, indent * 2})};
		size = {std::round(size.x - 2.0f), std::round(size.y - 2.0f)};
		sf::Vector2f position{this->getAreaPosition() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
		position = {std::round(position.x + 1.0f), std::round(position.y + 1.0f)};
		
		if(drawn || active) {
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			
			if(drawn && active) {
				rectangle.setFillColor(sf::Color(0, 255, 0, 60));
			} else if (drawn) {
				rectangle.setFillColor(sf::Color(255, 255, 0, 60));
			} else if (active) {
				rectangle.setFillColor(sf::Color(255, 0, 0, 60));
			}
			
			renderTarget.draw(rectangle);
		}
		
		active = false;
		drawn = false;
		
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	
	bool DecodePointer<BoxDebug>::decodePointer(const YAML::Node &node, BoxDebug *&boxDebug) {
		boxDebug = new BoxDebug{node["object"].as<IScalable *>()};
		return true;
	}
}