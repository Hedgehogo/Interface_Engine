#include "FnSizing.hpp"

#include <utility>

namespace ie {
	FnSizing::Make::Make(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn) :
		find_size_fn(std::move(find_size_fn)), get_parent_size_fn(std::move(get_parent_size_fn)){
	}
	
	FnSizing* FnSizing::Make::make(float normal_size) {
		return new FnSizing{std::move(*this), normal_size};
	}
	
	FnSizing::FnSizing(Make&& make, float normal_size) :
		find_size_fn_(std::move(make.find_size_fn)), get_parent_size_fn_(std::move(make.get_parent_size_fn)), normal_size_(normal_size) {
	}
	
	FnSizing::FnSizing(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn) :
		find_size_fn_(std::move(find_size_fn)), get_parent_size_fn_(std::move(get_parent_size_fn)), normal_size_() {
	}
	
	void FnSizing::init(float normal_size) {
		this->normal_size_ = normal_size;
	}
	
	float FnSizing::find_size(float parent_size, float target_size) {
		return find_size_fn_(parent_size, target_size, normal_size_);
	}
	
	float FnSizing::get_parent_size(float object_min_size) {
		return get_parent_size_fn_(object_min_size);
	}
	
	FnSizing* FnSizing::copy() {
		return new FnSizing{*this};
	}
}