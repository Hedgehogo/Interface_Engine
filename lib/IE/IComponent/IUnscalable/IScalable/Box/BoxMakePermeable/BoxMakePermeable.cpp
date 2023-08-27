#include "BoxMakePermeable.hpp"

namespace ie {
	BoxMakePermeable* BoxMakePermeable::Make::make(InitInfo initInfo) {
		return new BoxMakePermeable{std::move(*this), initInfo};
	}
	
	BoxMakePermeable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		object(std::move(object)), minSize(minSize) {
	}
	
	BoxMakePermeable::BoxMakePermeable(Make&& make, InitInfo initInfo) :
		Box(make.minSize), object(make.object->make(initInfo)) {
	}
	
	BoxMakePermeable::BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)) {
	}
	
	void BoxMakePermeable::init(InitInfo initInfo) {
		object->init(initInfo);
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