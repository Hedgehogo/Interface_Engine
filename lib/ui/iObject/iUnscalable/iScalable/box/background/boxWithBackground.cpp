#include "boxWithBackground.hpp"

namespace ui {
	BoxWithBackground::BoxWithBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset, sf::Vector2f minSize) :
		Box(minSize), object(object), background(background), offset(offset) {
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
	
	sf::Vector2f BoxWithBackground::getMinSize() const {
		return max(object->getMinSize() + offset * 2.f, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithBackground::getNormalSize() const {
		return max(object->getNormalSize() + offset * 2.f, background->getNormalSize());
	}
	
	IUninteractive& BoxWithBackground::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxWithBackground::getBackground() const {
		return *background;
	}
	
	IScalable& BoxWithBackground::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithBackground::getObject() const {
		return *object;
	}
	
	void BoxWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		background->resize(size, position);
		object->resize(size - offset * 2.f, position + offset);
	}
	
	bool BoxWithBackground::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	BoxWithBackground* BoxWithBackground::copy() {
		return new BoxWithBackground{*this};
	}
	
	void BoxWithBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		
	}
	
	bool DecodePointer<BoxWithBackground>::decodePointer(const YAML::Node& node, BoxWithBackground*& boxWithBackground) {
		boxWithBackground = new BoxWithBackground{
			node["object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IUninteractive> >(),
			convDef(node["offset"], sf::Vector2f{}),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}