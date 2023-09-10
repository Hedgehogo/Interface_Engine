#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IUnscalableLayout/IUnscalableTwoObjects/IUnscalableTwoObjects.hpp"

namespace ie {
	class IScalableTwoObjects : public virtual IScalableLayout, public virtual IUnscalableTwoObjects {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IUnscalableTwoObjects::Make {
			IScalableTwoObjects* make(InitInfo initInfo) override = 0;
		};
	};
}
