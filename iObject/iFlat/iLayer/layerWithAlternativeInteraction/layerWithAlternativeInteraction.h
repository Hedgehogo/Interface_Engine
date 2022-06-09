#pragma once
#include "../iLayer.h"

namespace ui {
	class LayerWithAlternativeInteraction : public ILayer {
	protected:
		IFlat* topObject;
		IFlat* bottomObject;
	
	public:
		LayerWithAlternativeInteraction(IFlat* topObject, IFlat* bottomObject, sf::Vector2f minimumSize);
		
		~LayerWithAlternativeInteraction() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
