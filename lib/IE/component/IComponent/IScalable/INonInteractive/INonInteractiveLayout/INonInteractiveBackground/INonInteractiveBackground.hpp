#pragma once

#include "../INonInteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"

namespace ie {
	class INonInteractiveBackground : public virtual INonInteractiveLayout, public virtual IScalableBackground {
	public:
		struct Make : public virtual INonInteractiveLayout::Make, public virtual IScalableBackground::Make {
			auto make(InitInfo init_info) -> INonInteractiveBackground* override = 0;
		};
	};
}
