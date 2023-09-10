#pragma once

#include "../IScalable.hpp"
#include "../../IUnscalableLayout/IUnscalableLayout.hpp"

namespace ie {
	class IScalableLayout : public virtual IUnscalableLayout, public virtual IScalable {
	public:
		struct Make : public virtual IUnscalableLayout::Make, public virtual IScalable::Make {
			IScalableLayout* make(InitInfo initInfo) override = 0;
		};
	};
}
