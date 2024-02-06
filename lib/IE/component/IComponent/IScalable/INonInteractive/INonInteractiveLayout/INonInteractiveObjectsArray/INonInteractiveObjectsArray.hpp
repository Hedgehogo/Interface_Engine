#pragma once

#include "../INonInteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class INonInteractiveObjectsArray : public virtual INonInteractiveLayout, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual INonInteractiveLayout::Make, public virtual IScalableObjectsArray::Make {
			INonInteractiveObjectsArray* make(InitInfo init_info) override = 0;
		};
	};
}
