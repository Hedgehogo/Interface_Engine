#include "BoxAlternative.hpp"
#include <algorithm>

namespace ie {
	BoxAlternative::Make::Make(BoxPtr<IScalable::Make>&& top_object, BoxPtr<IScalable::Make>&& bottom_object, sf::Vector2f min_size) :
		top_object(std::move(top_object)), bottom_object(std::move(bottom_object)), min_size(min_size) {
	}
	
	auto BoxAlternative::Make::make(InitInfo init_info) -> BoxAlternative* {
		return new BoxAlternative{std::move(*this), init_info};
	}
	
	BoxAlternative::BoxAlternative(Make&& make, InitInfo init_info) :
		Box(make.min_size), bottom_object_(make.bottom_object->make(init_info)), top_object_(make.top_object->make(init_info)) {
	}
	
	auto BoxAlternative::handle_event(Event event) -> bool {
		return top_object_->handle_event(event) || bottom_object_->handle_event(event);
	}
	
	auto BoxAlternative::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		top_object_->resize(size, position);
		bottom_object_->resize(size, position);
	}
	
	auto BoxAlternative::get_first_object() -> IScalable& {
		return *top_object_;
	}
	
	auto BoxAlternative::get_first_object() const -> IScalable const& {
		return *top_object_;
	}
	
	auto BoxAlternative::get_second_object() -> IScalable& {
		return *bottom_object_;
	}
	
	auto BoxAlternative::get_second_object() const -> IScalable const& {
		return *bottom_object_;
	}
}

auto ieml::Decode<char, ie::BoxAlternative::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxAlternative::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxAlternative::Make{
		map.at("top-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("bottom-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
