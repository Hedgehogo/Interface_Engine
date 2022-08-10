#include "layerWithAlternativeObject.hpp"
#include <algorithm>

namespace ui {
	LayerWithAlternativeObject::LayerWithAlternativeObject(ui::IScalable *topObject, ui::IScalable *bottomObject, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithTwoObjects(topObject, bottomObject) {
	}
	
	bool LayerWithAlternativeObject::updateInteractions(sf::Vector2f mousePosition) {
		return firstObject->updateInteractions(mousePosition) || secondObject->updateInteractions(mousePosition);
	}
	
	void LayerWithAlternativeObject::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		firstObject->resize(size, position);
		secondObject->resize(size, position);
	}
	
	LayerWithAlternativeObject *ui::LayerWithAlternativeObject::copy() {
		LayerWithAlternativeObject *layerWithAlternativeObject{new LayerWithAlternativeObject{firstObject->copy(), secondObject->copy(), minimumSize}};
		Layer::copy(layerWithAlternativeObject);
		return layerWithAlternativeObject;
	}
	
	LayerWithAlternativeObject *ui::LayerWithAlternativeObject::createFromYaml(const YAML::Node &node) {
		IScalable *topObject;
		IScalable *bottomObject;
		sf::Vector2f minSize{};
		
		node["top-object"] >> topObject;
		node["bottom-object"] >> bottomObject;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		return new LayerWithAlternativeObject{topObject, bottomObject, minSize};
	}
}
