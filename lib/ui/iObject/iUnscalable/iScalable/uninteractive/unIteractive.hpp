#pragma once
#include <SFML/Graphics.hpp>

#include "../iScalable.hpp"
#include "../../../../drawable/iDrawable/iDrawable.h"
#include "../../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IUninteractive : public virtual IScalable{
	public:
		bool updateInteractions(sf::Vector2f mousePosition) override;
        IUninteractive *copy() override = 0;
	};
}
