#pragma once
#include "../layer.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"

namespace ui {
	class LayerWithAlternativeObject : public Layer, public LayoutWithTwoObjects {
	public:
		LayerWithAlternativeObject(IScalable* topObject, IScalable* bottomObject, sf::Vector2f minSize = {});
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		LayerWithAlternativeObject* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithAlternativeObject *&layerWithAlternativeObject);
	
	typedef LayerWithAlternativeObject LayerWAObject;
	typedef LayerWithAlternativeObject LWAO;
}
