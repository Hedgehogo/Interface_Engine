#pragma once

#include "../iUnscalable.hpp"

namespace ui {
	class IScalable : public virtual IUnscalable {
	public:
		struct Make : public virtual IUnscalable::Make {
			virtual IScalable* make(InitInfo initInfo) = 0;
		};
		
		IScalable* copy() override = 0;
	};
}