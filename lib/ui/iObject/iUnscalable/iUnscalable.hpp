#pragma once
#include "../iObject.hpp"

namespace ui {
	class IUnscalable : public virtual IObject {
	public:
		IUnscalable* copy() override = 0;
	};
}
