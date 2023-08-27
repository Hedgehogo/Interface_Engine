#include "BoxBackground.hpp"

namespace ie {
	BoxBackground::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset, sf::Vector2f minSize) :
		object(std::move(object)), background(std::move(background)), offset(offset), minSize(minSize) {
	}
	
	BoxBackground* BoxBackground::Make::make(InitInfo initInfo) {
		return new BoxBackground{std::move(*this), initInfo};
	}
	
	BoxBackground::BoxBackground(Make&& make, InitInfo initInfo) :
		Box(make.minSize), background(make.background->make(initInfo)), object(make.object->make(initInfo)), offset(make.offset) {
	}
	
	BoxBackground::BoxBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset, sf::Vector2f minSize) :
		Box(minSize), background(std::move(background)), object(std::move(object)), offset(offset) {
	}
	
	void BoxBackground::init(InitInfo initInfo) {
		background->init(initInfo);
		object->init(initInfo);
	}
	
	void BoxBackground::setPosition(sf::Vector2f position) {
		layout.setPosition(position);
		background->setPosition(position);
		object->setPosition(position);
	}
	
	void BoxBackground::move(sf::Vector2f position) {
		layout.move(position);
		background->move(position);
		object->move(position);
	}
	
	void BoxBackground::setSize(sf::Vector2f size) {
		layout.setSize(size);
		background->setSize(size);
		object->setSize(size);
	}
	
	sf::Vector2f BoxBackground::getMinSize() const {
		return max(object->getMinSize() + offset * 2.f, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxBackground::getNormalSize() const {
		return max(object->getNormalSize() + offset * 2.f, background->getNormalSize());
	}
	
	IUninteractive& BoxBackground::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxBackground::getBackground() const {
		return *background;
	}
	
	IScalable& BoxBackground::getObject() {
		return *object;
	}
	
	const IScalable& BoxBackground::getObject() const {
		return *object;
	}
	
	void BoxBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		background->resize(size, position);
		object->resize(size - offset * 2.f, position + offset);
	}
	
	bool BoxBackground::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	BoxBackground* BoxBackground::copy() {
		return new BoxBackground{*this};
	}
	
	void BoxBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		
	}
	
	bool DecodePointer<BoxBackground>::decodePointer(const YAML::Node& node, BoxBackground*& boxWithBackground) {
		boxWithBackground = new BoxBackground{
			node["object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IUninteractive> >(),
			convDef(node["offset"], sf::Vector2f{}),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}