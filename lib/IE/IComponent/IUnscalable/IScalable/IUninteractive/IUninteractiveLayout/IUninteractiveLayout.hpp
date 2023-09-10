#pragma once

#include "../IUninteractive.hpp"
#include "../../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class IUninteractiveLayout : public virtual IScalableLayout, public virtual IUninteractive {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IUninteractive::Make {
			IUninteractiveLayout* make(InitInfo initInfo) override = 0;
		};
	};
}
