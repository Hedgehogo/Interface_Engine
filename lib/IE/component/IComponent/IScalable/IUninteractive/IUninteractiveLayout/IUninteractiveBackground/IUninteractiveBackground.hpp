#pragma once

#include "../IUninteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"

namespace ie {
	class IUninteractiveBackground : public virtual IUninteractiveLayout, public virtual IScalableBackground {
	public:
		struct Make : public virtual IUninteractiveLayout::Make, public virtual IScalableBackground::Make {
			IUninteractiveBackground* make(InitInfo init_info) override = 0;
		};
	};
}
