#pragma once

#include "../iAnimatorUnit.hpp"

namespace ui {
	class EmptyAnimatorUnit : public IAnimatorUnit{
	public:
		void restart() override;

		IAnimatorUnit *update(float time) override;

		void setNextUnit(IAnimatorUnit *nextUnit) override;
	};
} // ui