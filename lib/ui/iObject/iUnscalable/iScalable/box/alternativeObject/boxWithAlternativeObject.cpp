#include "boxWithAlternativeObject.hpp"
#include <algorithm>

namespace ui {
	BoxWithAlternativeObject::BoxWithAlternativeObject(IScalable *topObject, IScalable *bottomObject, sf::Vector2f minSize) :
		Box(minSize), LayoutWithTwoObjects(topObject, bottomObject) {
	}
	
	bool BoxWithAlternativeObject::updateInteractions(sf::Vector2f mousePosition) {
		return firstObject->updateInteractions(mousePosition) || secondObject->updateInteractions(mousePosition);
	}
	
	void BoxWithAlternativeObject::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		firstObject->resize(size, position);
		secondObject->resize(size, position);
	}
	
	BoxWithAlternativeObject *BoxWithAlternativeObject::copy() {
		BoxWithAlternativeObject *boxWithAlternativeObject{new BoxWithAlternativeObject{firstObject->copy(), secondObject->copy(), minimumSize}};
		Box::copy(boxWithAlternativeObject);
		return boxWithAlternativeObject;
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithAlternativeObject *&boxWithAlternativeObject) {
		IScalable *topObject;
		IScalable *bottomObject;
		sf::Vector2f minSize{};
		
		node["top-object"] >> topObject;
		node["bottom-object"] >> bottomObject;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithAlternativeObject = new BoxWithAlternativeObject{topObject, bottomObject, minSize};
		return true;
	}
	
	bool DecodePointer<BoxWithAlternativeObject>::decodePointer(const YAML::Node &node, BoxWithAlternativeObject *&boxWithAlternativeObject) {
		IScalable *topObject;
		IScalable *bottomObject;
		sf::Vector2f minSize{};
		
		node["top-object"] >> topObject;
		node["bottom-object"] >> bottomObject;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithAlternativeObject = new BoxWithAlternativeObject{topObject, bottomObject, minSize};
		return true;
	}
}
