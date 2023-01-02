#pragma once

#include "../../../../modules/appendix/yaml-animation/buffer.hpp"

namespace ui {
	class IAnimatorUnit {
	public:
		virtual void restart() = 0;

		virtual std::vector<IAnimatorUnit*> update(float time) = 0;

		virtual void setNextUnits(std::vector<IAnimatorUnit*> nextUnits) = 0;

		virtual void addNextUnits(IAnimatorUnit* nextUnit) = 0;

		virtual IAnimatorUnit* copy() = 0;

		virtual ~IAnimatorUnit() = default; 
	};
} // ui