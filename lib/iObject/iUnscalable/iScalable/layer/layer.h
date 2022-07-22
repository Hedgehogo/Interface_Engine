#pragma once
#include <SFML/Graphics.hpp>
#include "../iScalable.h"
#include "../../../layout/layout.h"
#include "../../../../enums/enums.h"

namespace ui {
	class Layer : public virtual IScalable, public virtual Layout {
	protected:
		sf::Vector2f minimumSize;
		
		void copy(Layer* layer);
	
	public:
		explicit Layer(sf::Vector2f minSize, sf::Vector2f size = {0.0f, 0.0f});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	};
}

