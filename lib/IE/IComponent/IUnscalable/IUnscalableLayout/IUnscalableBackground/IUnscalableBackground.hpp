#pragma once

#include "../IUnscalableLayout.hpp"
#include "../../../IComponentLayout/IComponentBackground/IComponentBackground.hpp"

namespace ie {
	class IUnscalableBackground : public virtual IUnscalableLayout, public virtual IComponentBackground {
	public:
		struct Make : public virtual IUnscalableLayout::Make, public virtual IComponentBackground::Make {
			IUnscalableBackground* make(InitInfo initInfo) override = 0;
		};
	};
}
