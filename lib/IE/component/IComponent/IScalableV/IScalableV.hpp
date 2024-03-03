#pragma once

#include "../IComponent.hpp"

namespace ie {
	class IScalableV : public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual auto make(InitInfo init_info) -> IScalableV* = 0;
		};
	};
}
