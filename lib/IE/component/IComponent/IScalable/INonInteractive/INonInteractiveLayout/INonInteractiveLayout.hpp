#pragma once

#include "../INonInteractive.hpp"
#include "../../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class INonInteractiveLayout : public virtual IScalableLayout, public virtual INonInteractive {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual INonInteractive::Make {
			INonInteractiveLayout* make(InitInfo init_info) override = 0;
		};
	};
}
