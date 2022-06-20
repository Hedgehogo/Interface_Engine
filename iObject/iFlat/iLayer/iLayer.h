#pragma once
#include <SFML/Graphics.hpp>
#include "../../../enums/enums.h"
#include "../iFlat.h"
namespace ui {
	class ILayer : public virtual IFlat {
	protected:
		sf::Vector2f minimumSize;
		
		sf::Vector2f position;
		sf::Vector2f size;
		
		void copy(ILayer* iLayer);
	
	public:
		explicit ILayer(sf::Vector2f minSize, sf::Vector2f size = {0.0f, 0.0f});
	};
}

