#pragma once

#include "../const/constSizing.hpp"
#include "../relative/normal/relativeNormalSizing.hpp"
#include "../relative/parent/relativeParentSizing.hpp"
#include "../coefficient/parent/parentCoefficientSizing.hpp"
#include "../coefficient/target/targetCoefficientSizing.hpp"
#include "../smart/smartSizing.hpp"
#include "../lambda/lambdaSizing.hpp"

namespace ui {
	ISizing* makeSize(bool relativeParent);
	
	ISizing* makeSize(float constSize);
	
	ISizing* makeSize(float coefficient, float addition, bool relativeTarget);
	
	ISizing* makeSize(float targetCoefficient, float parentCoefficient, float addition);
	
	ISizing* makeSize(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc);
}