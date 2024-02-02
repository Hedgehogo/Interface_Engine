#pragma once

#include "../INonInteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class INonInteractiveTwoObjects : public virtual INonInteractiveLayout, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual INonInteractiveLayout::Make, public virtual IScalableTwoObjects::Make {
			INonInteractiveTwoObjects* make(InitInfo init_info) override = 0;
		};
	};
}
