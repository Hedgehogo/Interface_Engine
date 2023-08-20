#pragma once

#include "../iObject.hpp"

namespace ui {
	class IUnscalable : public virtual IObject {
	public:
		struct Make : public virtual IObject::Make {
			virtual IUnscalable* make(InitInfo initInfo) = 0;
		};
		
		IUnscalable* copy() override = 0;
	};
}
