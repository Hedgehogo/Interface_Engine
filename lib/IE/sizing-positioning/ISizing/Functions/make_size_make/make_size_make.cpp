#include "make_size_make.hpp"

#include <utility>

namespace ie {
	ISizing::Make* make_size_make(bool relativeParent) {
		if(!relativeParent) {
			return new RelativeNormalSizing::Make{};
		}
		return new RelativeParentSizing::Make{};
	}
	
	ISizing::Make* make_size_make(float constSize) {
		return new ConstSizing::Make{constSize};
	}
	
	ISizing::Make* make_size_make(float coefficient, float addition, bool relativeTarget) {
		if(!relativeTarget) {
			return new ParentCoefficientSizing::Make{coefficient, addition};
		}
		return new TargetCoefficientSizing::Make{coefficient, addition};
	}
	
	ISizing::Make* make_size_make(float targetCoefficient, float parentCoefficient, float addition) {
		return new SmartSizing::Make{targetCoefficient, parentCoefficient, addition};
	}
	
	ISizing::Make* make_size_make(FnSizing::FindSizeFn findSizeFn, FnSizing::GetParentSizeFn getParentSizeFn) {
		return new FnSizing::Make{std::move(findSizeFn), std::move(getParentSizeFn)};
	}
}