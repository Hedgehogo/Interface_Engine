#pragma once

#include "../ISizing.hpp"
#include <functional>

namespace ie {
	class FnSizing : public virtual ISizing {
	public:
		using FindSizeFn = std::function<float(float parent_size, float target_size, float normal_size)>;
		using GetParentSizeFn = std::function<float(float object_min_size)>;
		
		struct Make : public virtual ISizing::Make {
			FindSizeFn find_size_fn;
			GetParentSizeFn get_parent_size_fn;
			
			Make() = default;
			
			Make(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn);
			
			auto make(float normal_size) -> FnSizing* override;
		};
		
		FnSizing(Make&& make, float normal_size);
		
		FnSizing(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn);
		
		auto find_size(float parent_size, float target_size) -> float override;
		
		auto get_parent_size(float object_min_size) -> float override;
		
	protected:
		FindSizeFn find_size_fn_;
		GetParentSizeFn get_parent_size_fn_;
		float normal_size_;
	};
}
