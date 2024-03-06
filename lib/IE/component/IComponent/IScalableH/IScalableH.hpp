#pragma once

#include "../IComponent.hpp"

namespace ie {
	class IScalableH : public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual auto make(InitInfo init_info) -> IScalableH* = 0;
		};
	};
}
