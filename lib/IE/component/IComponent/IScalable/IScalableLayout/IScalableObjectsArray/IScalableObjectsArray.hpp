#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IComponentLayout/IComponentObjectsArray/IComponentObjectsArray.hpp"

namespace ie {
	class IScalableObjectsArray : public virtual IScalableLayout, public virtual IComponentObjectsArray {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IComponentObjectsArray::Make {
			auto make(InitInfo init_info) -> IScalableObjectsArray* override = 0;
		};
	};
}
