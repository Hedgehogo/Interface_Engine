#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IUnscalableLayout/IUnscalableBackground/IUnscalableBackground.hpp"

namespace ie {
	class IScalableBackground : public virtual IScalableLayout, public virtual IUnscalableBackground {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IUnscalableBackground::Make {
			IScalableBackground* make(InitInfo initInfo) override = 0;
		};
	};
}
