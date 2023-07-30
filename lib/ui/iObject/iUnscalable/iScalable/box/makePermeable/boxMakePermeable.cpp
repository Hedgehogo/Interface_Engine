#include "boxMakePermeable.hpp"

namespace ui {
	BoxMakePermeable::BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)) {
	}
	
	void BoxMakePermeable::init(InitInfo initInfo) {
		object->init(initInfo);
	}
	
	void BoxMakePermeable::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutWithObject::resize(size, position);
	}
	
	bool BoxMakePermeable::updateInteractions(sf::Vector2f mousePosition) {
		object->updateInteractions(mousePosition);
		return false;
	}
	
	IScalable& BoxMakePermeable::getObject() {
		return *object;
	}
	
	const IScalable& BoxMakePermeable::getObject() const {
		return *object;
	}
	
	BoxMakePermeable* BoxMakePermeable::copy() {
		return new BoxMakePermeable{*this};
	}
	
	bool DecodePointer<BoxMakePermeable>::decodePointer(const YAML::Node& node, BoxMakePermeable*& boxMakePermeable) {
		boxMakePermeable = new BoxMakePermeable{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}