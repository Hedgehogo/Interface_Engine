#pragma once
#include "../layer.h"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.h"

namespace ui {
	class LayerWithAlternativeObject : public Layer, public LayoutWithTwoObjects {
	public:
		LayerWithAlternativeObject(IScalable* topObject, IScalable* bottomObject, sf::Vector2f minimumSize = {});
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		LayerWithAlternativeObject* copy() override;
	};
	
	typedef LayerWithAlternativeObject LayerWAObject;
	typedef LayerWithAlternativeObject LWAO;
}
