#include "make_size_make.hpp"

#include <utility>

namespace ie {
	ISizing::Make* make_size_make(bool relative_parent) {
		if(!relative_parent) {
			return new RelativeNormalSizing::Make{};
		}
		return new RelativeParentSizing::Make{};
	}
	
	ISizing::Make* make_size_make(float const_size) {
		return new ConstSizing::Make{const_size};
	}
	
	ISizing::Make* make_size_make(float coefficient, float addition, bool relative_target) {
		if(!relative_target) {
			return new ParentCoefficientSizing::Make{coefficient, addition};
		}
		return new TargetCoefficientSizing::Make{coefficient, addition};
	}
	
	ISizing::Make* make_size_make(float target_coefficient, float parent_coefficient, float addition) {
		return new SmartSizing::Make{target_coefficient, parent_coefficient, addition};
	}
	
	ISizing::Make* make_size_make(FnSizing::FindSizeFn find_size_fn, FnSizing::GetParentSizeFn get_parent_size_fn) {
		return new FnSizing::Make{std::move(find_size_fn), std::move(get_parent_size_fn)};
	}
}