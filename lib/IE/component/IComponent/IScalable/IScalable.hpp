#pragma once

#include "../IComponent.hpp"

namespace ie {
	class IScalable : public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual IScalable* make(InitInfo init_info) = 0;
		};
		
		IScalable* copy() override = 0;
	};
}