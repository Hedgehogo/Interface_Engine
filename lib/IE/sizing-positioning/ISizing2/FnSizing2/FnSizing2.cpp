#include "FnSizing2.hpp"

namespace ie {
	FnSizing2::Make::Make(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn) :
		find_size_fn((find_size_fn)),
		get_parent_size_fn((get_parent_size_fn)) {
	}
	
	auto FnSizing2::Make::make(Sizing2InitInfo init_info) -> FnSizing2* {
		return new FnSizing2{std::move(*this), init_info};
	}
	
	FnSizing2::FnSizing2(Make&& make, Sizing2InitInfo init_info) :
		find_size_fn_(std::move(make.find_size_fn)),
		get_parent_size_fn_(std::move(make.get_parent_size_fn)),
		render_target_(&init_info.render_target),
		normal_size_(init_info.normal_size) {
	}
	
	FnSizing2::FnSizing2(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn) :
		find_size_fn_(std::move(find_size_fn)), get_parent_size_fn_(std::move(get_parent_size_fn)), render_target_(nullptr), normal_size_() {
	}
	
	auto FnSizing2::find_size(sf::Vector2f parent_size) -> sf::Vector2f {
		sf::Vector2f target_size{render_target_->getSize()};
		return find_size_fn_(parent_size, target_size, normal_size_);
	}
	
	auto FnSizing2::get_parent_size(sf::Vector2f object_size) -> sf::Vector2f {
		return get_parent_size_fn_(object_size);
	}
}