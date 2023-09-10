#pragma once

#include "../IUnscalableLayout.hpp"
#include "../../../IComponentLayout/IComponentObjectsArray/IComponentObjectsArray.hpp"

namespace ie {
	class IUnscalableObjectsArray : public virtual IUnscalableLayout, public virtual IComponentObjectsArray {
	public:
		struct Make : public virtual IUnscalableLayout::Make, public virtual IComponentObjectsArray::Make {
			IUnscalableObjectsArray* make(InitInfo initInfo) override = 0;
		};
	};
}
