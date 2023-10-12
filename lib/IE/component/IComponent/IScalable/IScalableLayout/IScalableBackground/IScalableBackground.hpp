#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IComponentLayout/IComponentBackground/IComponentBackground.hpp"

namespace ie {
	class IScalableBackground : public virtual IScalableLayout, public virtual IComponentBackground {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IComponentBackground::Make {
			IScalableBackground* make(InitInfo initInfo) override = 0;
		};
	};
}
