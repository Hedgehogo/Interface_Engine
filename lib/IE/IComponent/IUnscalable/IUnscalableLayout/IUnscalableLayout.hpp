#pragma once

#include "../IUnscalable.hpp"
#include "../../IComponentLayout/IComponentLayout.hpp"

namespace ie {
	class IUnscalableLayout : public virtual IComponentLayout, public virtual IUnscalable {
	public:
		struct Make : public virtual IComponentLayout::Make, public virtual IUnscalable::Make {
			IUnscalableLayout* make(InitInfo initInfo) override = 0;
		};
	};
}
