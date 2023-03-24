#include "boxUninteractive.hpp"

namespace ui {
	BoxUninteractive::BoxUninteractive(IScalable *object, sf::Vector2f minSize) : LayoutWithObject(object), Box(minSize) {
	}
	
	void BoxUninteractive::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithObject::resize(size, position);
	}
	
	bool BoxUninteractive::updateInteractions(sf::Vector2f mousePosition) {
		return IUninteractive::updateInteractions(mousePosition);
	}
	
	bool convertPointer(const YAML::Node &node, BoxUninteractive *&boxUninteractive) {
		IScalable *object;
		sf::Vector2f minSize;
		node["object"] >> object;
		if(node["min-size"])
			node["min-size"] >> minSize;
		boxUninteractive = new BoxUninteractive{object, minSize};
		return true;
	}
	
	BoxUninteractive *BoxUninteractive::copy() {
		return new BoxUninteractive{object->copy(), minimumSize};
	}
}