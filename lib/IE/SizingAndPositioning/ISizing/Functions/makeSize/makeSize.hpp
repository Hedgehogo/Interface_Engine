#pragma once

#include "../../ConstSizing/ConstSizing.hpp"
#include "../../RelativeNormalSizing/RelativeNormalSizing.hpp"
#include "../../RelativeParentSizing/RelativeParentSizing.hpp"
#include "../../ParentCoefficientSizing/ParentCoefficientSizing.hpp"
#include "../../TargetCoefficientSizing/TargetCoefficientSizing.hpp"
#include "../../SmartSizing/SmartSizing.hpp"
#include "../../LambdaSizing/LambdaSizing.hpp"

namespace ui {
	ISizing* makeSize(bool relativeParent);
	
	ISizing* makeSize(float constSize);
	
	ISizing* makeSize(float coefficient, float addition, bool relativeTarget);
	
	ISizing* makeSize(float targetCoefficient, float parentCoefficient, float addition);
	
	ISizing* makeSize(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc);
}