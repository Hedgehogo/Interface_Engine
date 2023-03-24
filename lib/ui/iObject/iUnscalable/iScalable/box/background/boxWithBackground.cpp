#include "boxWithBackground.hpp"

namespace ui {
	BoxWithBackground::BoxWithBackground(IScalable *object, IUninteractive *background, sf::Vector2f offset, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), LayoutWithBackground(background), offset(offset) {
	}
	
	void BoxWithBackground::init(InitInfo initInfo) {
		background->init(initInfo);
		object->init(initInfo);
	}
	
	void BoxWithBackground::setPosition(sf::Vector2f position) {
		background->setPosition(position);
		object->setPosition(position);
	}
	
	void BoxWithBackground::move(sf::Vector2f position) {
		background->move(position);
		object->move(position);
	}
	
	void BoxWithBackground::setSize(sf::Vector2f size) {
		background->setSize(size);
		object->setSize(size);
	}
	
	sf::Vector2f BoxWithBackground::getMinSize() {
		return max(object->getMinSize() + offset * 2.f, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithBackground::getNormalSize() {
		return max(object->getNormalSize() + offset * 2.f, background->getNormalSize());
	}
	
	void BoxWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		background->resize(size, position);
		object->resize(size - offset * 2.f, position + offset);
	}
	
	bool BoxWithBackground::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	BoxWithBackground *BoxWithBackground::copy() {
		return new BoxWithBackground(object->copy(), background->copy(), offset, minimumSize);
	}
	
	void BoxWithBackground::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithBackground *&boxWithBackground) {
		IScalable *object;
		IUninteractive *background;
		sf::Vector2f offset{};
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		node["background"] >> background;
		if(node["offset"])
			node["offset"] >> offset;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithBackground = new BoxWithBackground{object, background, offset, minSize};
		return true;
	}
}