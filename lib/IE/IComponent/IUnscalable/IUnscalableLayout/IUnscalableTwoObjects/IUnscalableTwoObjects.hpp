#pragma once

#include "../IUnscalableLayout.hpp"
#include "../../../IComponentLayout/IComponentTwoObjects/IComponentTwoObjects.hpp"

namespace ie {
	class IUnscalableTwoObjects : public virtual IUnscalableLayout, public virtual IComponentTwoObjects {
	public:
		struct Make : public virtual IUnscalableLayout::Make, public virtual IComponentTwoObjects::Make {
			IUnscalableTwoObjects* make(InitInfo initInfo) override = 0;
		};
	};
}
