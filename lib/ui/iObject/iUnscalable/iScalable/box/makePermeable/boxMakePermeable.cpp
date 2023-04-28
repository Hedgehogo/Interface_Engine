#include "boxMakePermeable.hpp"

namespace ui {
	BoxMakePermeable::BoxMakePermeable(IScalable *object, sf::Vector2f minSize) : Box(minSize), LayoutWithObject(object) {
	}
	
	void BoxMakePermeable::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithObject::resize(size, position);
	}
	
	bool BoxMakePermeable::updateInteractions(sf::Vector2f mousePosition) {
		object->updateInteractions(mousePosition);
		return false;
	}
	
	BoxMakePermeable *BoxMakePermeable::copy() {
		BoxMakePermeable *boxMakePermeable{new BoxMakePermeable{object->copy(), minimumSize}};
		Box::copy(boxMakePermeable);
		return boxMakePermeable;
	}
	
	bool convertPointer(const YAML::Node &node, BoxMakePermeable *&boxMakePermeable) {
		IScalable *object;
		sf::Vector2f minSize{};
		node["object"] >> object;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxMakePermeable = new BoxMakePermeable{object, minSize};
		return true;
	}
	
	bool DecodePointer<BoxMakePermeable>::decodePointer(const YAML::Node &node, BoxMakePermeable *&boxMakePermeable) {
		IScalable *object;
		sf::Vector2f minSize{};
		node["object"] >> object;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxMakePermeable = new BoxMakePermeable{object, minSize};
		return true;
	}
}