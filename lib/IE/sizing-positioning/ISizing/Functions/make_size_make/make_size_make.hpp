#pragma once

#include "../../ConstSizing/ConstSizing.hpp"
#include "../../RelativeNormalSizing/RelativeNormalSizing.hpp"
#include "../../RelativeParentSizing/RelativeParentSizing.hpp"
#include "../../ParentCoefficientSizing/ParentCoefficientSizing.hpp"
#include "../../TargetCoefficientSizing/TargetCoefficientSizing.hpp"
#include "../../SmartSizing/SmartSizing.hpp"
#include "../../FnSizing/FnSizing.hpp"

namespace ie {
	ISizing::Make* make_size_make(bool relative_parent);
	
	ISizing::Make* make_size_make(float const_size);
	
	ISizing::Make* make_size_make(float coefficient, float addition, bool relative_target);
	
	ISizing::Make* make_size_make(float target_coefficient, float parent_coefficient, float addition);
	
	ISizing::Make* make_size_make(FnSizing::FindSizeFn find_size_fn, FnSizing::GetParentSizeFn get_parent_size_fn);
}