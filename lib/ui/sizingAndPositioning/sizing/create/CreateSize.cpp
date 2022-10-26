#include "CreateSize.hpp"

namespace ui {

	Sizing *createSize(bool relativeParent) {
		if(!relativeParent) {
			return new RelativeNormalSizing{};
		}
		return new RelativeParentSizing{};
	}

	Sizing *createSize(float coefficient, float addition, bool relativeTarget) {
		if(!relativeTarget) {
			return new ParentCoefficientSizing{coefficient, addition};
		}
		return new TargetCoefficientSizing{coefficient, addition};
	}

} // ui