#pragma once

#include "../IUninteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class IUninteractiveObjectsArray : public virtual IUninteractiveLayout, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual IUninteractiveLayout::Make, public virtual IScalableObjectsArray::Make {
			IUninteractiveObjectsArray* make(InitInfo init_info) override = 0;
		};
	};
}
