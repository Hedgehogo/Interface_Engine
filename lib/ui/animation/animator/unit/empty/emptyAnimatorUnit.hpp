#pragma once

#include "../iAnimatorUnit.hpp"

namespace ui {
	class EmptyAnimatorUnit : public IAnimatorUnit{
	public:
		void restart() override;

		std::vector<IAnimatorUnit*> update(float time) override;

		void setNextUnits(std::vector<IAnimatorUnit*> nextUnits) override;

		void addNextUnits(IAnimatorUnit* nextUnit) override;
	};
} // ui