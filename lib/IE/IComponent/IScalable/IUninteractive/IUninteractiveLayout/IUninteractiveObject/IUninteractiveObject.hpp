#pragma once

#include "../IUninteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class IUninteractiveObject : public virtual IUninteractiveLayout, public virtual IScalableObject {
	public:
		struct Make : public virtual IUninteractiveLayout::Make, public virtual IScalableObject::Make {
			IUninteractiveObject* make(InitInfo initInfo) override = 0;
		};
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	};
}
