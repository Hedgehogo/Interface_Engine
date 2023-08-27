#include "makeSize.hpp"

#include <utility>

namespace ie {
	ISizing::Make* makeSizeMake(bool relativeParent) {
		if(!relativeParent) {
			return new RelativeNormalSizing::Make{};
		}
		return new RelativeParentSizing::Make{};
	}
	
	ISizing::Make* makeSizeMake(float constSize) {
		return new ConstSizing::Make{constSize};
	}
	
	ISizing::Make* makeSizeMake(float coefficient, float addition, bool relativeTarget) {
		if(!relativeTarget) {
			return new ParentCoefficientSizing::Make{coefficient, addition};
		}
		return new TargetCoefficientSizing::Make{coefficient, addition};
	}
	
	ISizing::Make* makeSizeMake(float targetCoefficient, float parentCoefficient, float addition) {
		return new SmartSizing::Make{targetCoefficient, parentCoefficient, addition};
	}
	
	ISizing::Make* makeSizeMake(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc) {
		return new LambdaSizing::Make{std::move(findSizeFunc), std::move(minSizeFunc)};
	}
}