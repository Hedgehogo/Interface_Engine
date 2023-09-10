#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IUnscalableLayout/IUnscalableObjectsArray/IUnscalableObjectsArray.hpp"

namespace ie {
	class IScalableObjectsArray : public virtual IScalableLayout, public virtual IUnscalableObjectsArray {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IUnscalableObjectsArray::Make {
			IScalableObjectsArray* make(InitInfo initInfo) override = 0;
		};
	};
}
