#pragma once

#include "../IScalable.hpp"
#include "../../IComponentLayout/IComponentLayout.hpp"

namespace ie {
	class IScalableLayout : public virtual IComponentLayout, public virtual IScalable {
	public:
		struct Make : public virtual IComponentLayout::Make, public virtual IScalable::Make {
			IScalableLayout* make(InitInfo initInfo) override = 0;
		};
	};
}
