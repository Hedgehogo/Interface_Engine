#pragma once

#include "../IScalableV/IScalableV.hpp"
#include "../IScalableH/IScalableH.hpp"

namespace ie {
	class IScalable : public virtual IScalableV, public virtual IScalableH {
	public:
		struct Make : public virtual IScalableV::Make, public virtual IScalableH::Make {
			virtual auto make(InitInfo init_info) -> IScalable* = 0;
		};
	};
}
