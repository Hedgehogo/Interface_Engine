#pragma once
#include <SFML/Graphics.hpp>

#include "../iScalable.hpp"
#include "../../../../drawable/iDrawable/iDrawable.hpp"
#include "../../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	class IUninteractive : public virtual IScalable {
	public:
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
        IUninteractive *copy() override = 0;
	};
}
