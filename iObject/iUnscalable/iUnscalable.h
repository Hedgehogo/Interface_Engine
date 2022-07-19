#pragma once
#include "../iObject.h"

namespace ui {
	class IUnscalable : public virtual IObject {
	public:
		IUnscalable* copy() override = 0;
	};
}
