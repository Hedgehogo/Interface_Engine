#pragma once

#include "../iUnscalable.hpp"

namespace ui {
	class IScalable : public virtual IUnscalable {
	public:
		IScalable* copy() override = 0;
	};
}