#pragma once

#include "../IComponent.hpp"

namespace ie {
	class IUnscalable : public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual IUnscalable* make(InitInfo initInfo) = 0;
		};
		
		IUnscalable* copy() override = 0;
	};
}
