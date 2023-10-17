#pragma once

#include "../../ConstSizing/ConstSizing.hpp"
#include "../../RelativeNormalSizing/RelativeNormalSizing.hpp"
#include "../../RelativeParentSizing/RelativeParentSizing.hpp"
#include "../../ParentCoefficientSizing/ParentCoefficientSizing.hpp"
#include "../../TargetCoefficientSizing/TargetCoefficientSizing.hpp"
#include "../../SmartSizing/SmartSizing.hpp"
#include "../../FnSizing/FnSizing.hpp"

namespace ie {
	ISizing::Make* make_size_make(bool relativeParent);
	
	ISizing::Make* make_size_make(float constSize);
	
	ISizing::Make* make_size_make(float coefficient, float addition, bool relativeTarget);
	
	ISizing::Make* make_size_make(float targetCoefficient, float parentCoefficient, float addition);
	
	ISizing::Make* make_size_make(FnSizing::FindSizeFn findSizeFn, FnSizing::GetParentSizeFn getParentSizeFn);
}