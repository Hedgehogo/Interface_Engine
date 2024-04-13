#include "BoxConstBezel.hpp"

namespace ie {
	BoxConstBezel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<INonInteractive::Make>&& bezel, float thickness, sf::Vector2f min_size) :
		object(std::move(object)), bezel(std::move(bezel)), thickness(thickness), min_size(min_size) {
	}
	
	auto BoxConstBezel::Make::make(InitInfo init_info) -> BoxConstBezel* {
		return new BoxConstBezel{std::move(*this), init_info};
	}
	
	BoxConstBezel::BoxConstBezel(Make&& make, InitInfo init_info) :
		Box(make.min_size), bezel_(make.bezel->make(init_info)), object_(make.object->make(init_info)), thickness_(make.thickness) {
	}
	
	auto BoxConstBezel::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		bezel_->resize(size, position);
		object_->resize(size - sf::Vector2f(thickness_ * 2.0f, thickness_ * 2.0f), position + sf::Vector2f(thickness_, thickness_));
	}
	
	auto BoxConstBezel::update_interactions(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			if(object_->in_area(sf::Vector2f{touch.position})) {
				return object_->update_interactions(event);
			}
			return bezel_->update_interactions(event);
		}).some_or_else([=] {
			return object_->update_interactions(event) || bezel_->update_interactions(event);
		});
	}
	
	auto BoxConstBezel::get_min_size() const -> sf::Vector2f {
		return max(object_->get_min_size() + sf::Vector2f{thickness_ * 2, thickness_ * 2}, bezel_->get_min_size(), minimum_size_);
	}
	
	auto BoxConstBezel::get_normal_size() const -> sf::Vector2f {
		return max(object_->get_normal_size() + sf::Vector2f{thickness_ * 2, thickness_ * 2}, bezel_->get_normal_size());
	}
	
	auto BoxConstBezel::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxConstBezel::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxConstBezel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		bezel_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxConstBezel::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxConstBezel::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxConstBezel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("bezel").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.at("thickness").except().as<float>().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
