#pragma once

#include "../INonInteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"

namespace ie {
	class INonInteractiveBackground : public virtual INonInteractiveLayout, public virtual IScalableBackground {
	public:
		struct Make : public virtual INonInteractiveLayout::Make, public virtual IScalableBackground::Make {
			INonInteractiveBackground* make(InitInfo init_info) override = 0;
		};
	};
}
