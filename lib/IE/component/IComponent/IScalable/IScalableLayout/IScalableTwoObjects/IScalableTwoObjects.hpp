#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IComponentLayout/IComponentTwoObjects/IComponentTwoObjects.hpp"

namespace ie {
	class IScalableTwoObjects : public virtual IScalableLayout, public virtual IComponentTwoObjects {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IComponentTwoObjects::Make {
			IScalableTwoObjects* make(InitInfo init_info) override = 0;
		};
	};
}
