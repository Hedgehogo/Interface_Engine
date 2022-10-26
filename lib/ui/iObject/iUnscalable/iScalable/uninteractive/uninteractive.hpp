#pragma once

#include "../iScalable.hpp"

namespace ui {
	class IUninteractive : public virtual IScalable {
	public:
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
        IUninteractive *copy() override = 0;
	};
}
