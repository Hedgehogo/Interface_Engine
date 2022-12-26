#pragma once

#include "../../../../modules/appendix/yaml-animation/buffer.hpp"

namespace ui {
	class IAnimatorUnit {
	public:
		virtual void restart() = 0;

		virtual IAnimatorUnit* update(float time) = 0;

		virtual void setNextUnit(IAnimatorUnit *nextUnit) = 0;
		
		virtual ~IAnimatorUnit() = default; 
	};
} // ui