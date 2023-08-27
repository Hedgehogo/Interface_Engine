#pragma once

#include "../../ConstSizing/ConstSizing.hpp"
#include "../../RelativeNormalSizing/RelativeNormalSizing.hpp"
#include "../../RelativeParentSizing/RelativeParentSizing.hpp"
#include "../../ParentCoefficientSizing/ParentCoefficientSizing.hpp"
#include "../../TargetCoefficientSizing/TargetCoefficientSizing.hpp"
#include "../../SmartSizing/SmartSizing.hpp"
#include "../../LambdaSizing/LambdaSizing.hpp"

namespace ie {
	ISizing::Make* makeSizeMake(bool relativeParent);
	
	ISizing::Make* makeSizeMake(float constSize);
	
	ISizing::Make* makeSizeMake(float coefficient, float addition, bool relativeTarget);
	
	ISizing::Make* makeSizeMake(float targetCoefficient, float parentCoefficient, float addition);
	
	ISizing::Make* makeSizeMake(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc);
}