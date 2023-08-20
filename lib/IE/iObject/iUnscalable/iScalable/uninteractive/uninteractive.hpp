#pragma once

#include "../iScalable.hpp"

namespace ui {
	class IUninteractive : public virtual IScalable {
	public:
		struct Make : public virtual IScalable::Make {
			virtual IUninteractive* make(InitInfo initInfo) = 0;
		};
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		IUninteractive* copy() override = 0;
	};
}
