#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class IScalableObject : public virtual IScalableLayout, public virtual IComponentObject {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IComponentObject::Make {
			IScalableObject* make(InitInfo init_info) override = 0;
		};
	};
}
