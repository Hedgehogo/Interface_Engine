#pragma once
#include <SFML/Graphics.hpp>
#include "../../../enums/enums.h"
#include "../iFlat.h"
#include "../../layout/layout.h"

namespace ui {
	class ILayer : public virtual IFlat, public Layout {
	protected:
		sf::Vector2f minimumSize;
		
		void copy(ILayer* iLayer);
	
	public:
		explicit ILayer(sf::Vector2f minSize, sf::Vector2f size = {0.0f, 0.0f});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	};
}

