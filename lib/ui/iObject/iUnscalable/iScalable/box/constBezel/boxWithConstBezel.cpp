#include "boxWithConstBezel.hpp"
#include "../../../../../drawable/manager/drawManager.hpp"

namespace ui {
	BoxWithConstBezel::BoxWithConstBezel(IScalable *object, IUninteractive *bezel, float thickness, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), bezel(bezel), thickness(thickness) {
		sf::Vector2f minimumSize{object->getMinSize() + sf::Vector2f(thickness * 2.0f, thickness * 2.0f)};
		if(this->minimumSize.x < minimumSize.x) {
			this->minimumSize.x = minimumSize.x;
		}
		if(this->minimumSize.y < minimumSize.y) {
			this->minimumSize.y = minimumSize.y;
		}
	}
	
	void BoxWithConstBezel::init(InitInfo initInfo) {
		bezel->init(initInfo);
		object->init(initInfo);
	}
	
	BoxWithConstBezel::~BoxWithConstBezel() {
		delete bezel;
	}
	
	void BoxWithConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool BoxWithConstBezel::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return false;
	}
	
	sf::Vector2f BoxWithConstBezel::getMinSize() {
		return max(object->getMinSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithConstBezel::getNormalSize() {
		return max(object->getNormalSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getNormalSize());
	}
	
	BoxWithConstBezel *BoxWithConstBezel::copy() {
		BoxWithConstBezel *boxWithConstBezel{new BoxWithConstBezel{object->copy(), bezel->copy(), thickness}};
		Box::copy(boxWithConstBezel);
		return boxWithConstBezel;
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithConstBezel *&boxWithConstBezel) {
		IScalable *object;
		IUninteractive *bezel;
		float thickness;
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		node["bezel"] >> bezel;
		node["thickness"] >> thickness;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithConstBezel = new BoxWithConstBezel{object, bezel, thickness, minSize};
		return true;
	}
	
	bool DecodePointer<BoxWithConstBezel>::decodePointer(const YAML::Node &node, BoxWithConstBezel *&boxWithConstBezel) {
		IScalable *object;
		IUninteractive *bezel;
		float thickness;
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		node["bezel"] >> bezel;
		node["thickness"] >> thickness;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithConstBezel = new BoxWithConstBezel{object, bezel, thickness, minSize};
		return true;
	}
	
	void BoxWithConstBezel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		bezel->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
}

