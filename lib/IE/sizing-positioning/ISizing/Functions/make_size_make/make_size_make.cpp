#include "make_size_make.hpp"

#include <utility>

namespace ie {
	auto make_size_make(bool relative_parent) -> ISizing::Make* {
		if(!relative_parent) {
			return new RelativeNormalSizing::Make{};
		}
		return new RelativeParentSizing::Make{};
	}
	
	auto make_size_make(float const_size) -> ISizing::Make* {
		return new ConstSizing::Make{const_size};
	}
	
	auto make_size_make(float coefficient, float addition, bool relative_target) -> ISizing::Make* {
		if(!relative_target) {
			return new ParentCoefficientSizing::Make{coefficient, addition};
		}
		return new TargetCoefficientSizing::Make{coefficient, addition};
	}
	
	auto make_size_make(float target_coefficient, float parent_coefficient, float addition) -> ISizing::Make* {
		return new SmartSizing::Make{target_coefficient, parent_coefficient, addition};
	}
	
	auto make_size_make(FnSizing::FindSizeFn find_size_fn, FnSizing::GetParentSizeFn get_parent_size_fn) -> ISizing::Make* {
		return new FnSizing::Make{std::move(find_size_fn), std::move(get_parent_size_fn)};
	}
}