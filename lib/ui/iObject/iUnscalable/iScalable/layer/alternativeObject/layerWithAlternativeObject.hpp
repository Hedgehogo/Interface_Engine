#pragma once
#include "../layer.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.h"

namespace ui {
	class LayerWithAlternativeObject : public Layer, public LayoutWithTwoObjects {
	public:
		LayerWithAlternativeObject(IScalable* topObject, IScalable* bottomObject, sf::Vector2f minSize = {});
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		static LayerWithAlternativeObject* createFromYaml(const YAML::Node &node);
		
		LayerWithAlternativeObject* copy() override;
	};
	
	typedef LayerWithAlternativeObject LayerWAObject;
	typedef LayerWithAlternativeObject LWAO;
}
