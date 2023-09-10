#pragma once

#include "../IUnscalableLayout.hpp"
#include "../../../IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class IUnscalableObject : public virtual IUnscalableLayout, public virtual IComponentObject {
	public:
		struct Make : public virtual IUnscalableLayout::Make, public virtual IComponentObject::Make {
			IUnscalableObject* make(InitInfo initInfo) override = 0;
		};
	};
}
