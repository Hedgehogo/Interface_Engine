#include "makeSize.hpp"

#include <utility>

namespace ui {
	ISizing *makeSize(bool relativeParent) {
		if(!relativeParent) {
			return new RelativeNormalSizing{};
		}
		return new RelativeParentSizing{};
	}
	
	ISizing *makeSize(float constSize) {
		return new ConstSizing{constSize};
	}

	ISizing *makeSize(float coefficient, float addition, bool relativeTarget) {
		if(!relativeTarget) {
			return new ParentCoefficientSizing{coefficient, addition};
		}
		return new TargetCoefficientSizing{coefficient, addition};
	}
	
	ISizing *makeSize(float targetCoefficient, float parentCoefficient, float addition) {
		return new SmartSizing{targetCoefficient, parentCoefficient, addition};
	}
	
	ISizing *makeSize(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc) {
		return new LambdaSizing{std::move(findSizeFunc), std::move(minSizeFunc)};
	}
}