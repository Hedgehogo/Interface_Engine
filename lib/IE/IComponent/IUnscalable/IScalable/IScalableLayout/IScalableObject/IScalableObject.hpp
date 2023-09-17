#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IUnscalableLayout/IUnscalableObject/IUnscalableObject.hpp"

namespace ie {
	class IScalableObject : public virtual IScalableLayout, public virtual IUnscalableObject {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IUnscalableObject::Make {
			IScalableObject* make(InitInfo initInfo) override = 0;
		};
	};
}
