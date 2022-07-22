#pragma once
#include "../iUnscalable.h"

namespace ui {
	class IScalable : public virtual IUnscalable {
	public:
		IScalable* copy() override = 0;
	};
}