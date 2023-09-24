#pragma once

#include "../IUninteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class IUninteractiveTwoObjects : public virtual IUninteractiveLayout, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual IUninteractiveLayout::Make, public virtual IScalableTwoObjects::Make {
			IUninteractiveTwoObjects* make(InitInfo initInfo) override = 0;
		};
	};
}
