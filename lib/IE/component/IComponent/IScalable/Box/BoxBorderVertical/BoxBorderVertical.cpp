#include "BoxBorderVertical.hpp"
#include <vector>

namespace ie {
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(std::move(add_bounds(bounds))), min_size(min_size) {
	}
	
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(gen_bounds(this->objects.size())), min_size(min_size) {
	}
	
	BoxBorderVertical::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		float bound,
		sf::Vector2f min_size
	) :
		objects(make_vector(std::move(first_object), std::move(second_object))), bounds({0.f, bound, 1.f}), min_size(min_size) {
	}
	
	auto BoxBorderVertical::Make::make(InitInfo init_info) -> BoxBorderVertical* {
		return new BoxBorderVertical{std::move(*this), init_info};
	}
	
	BoxBorderVertical::BoxBorderVertical(Make&& make, InitInfo init_info) :
		Box(make.min_size), objects_(map_make(std::move(make.objects), init_info)), bounds_(std::move(make.bounds)) {
	}
	
	auto BoxBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		auto coordinate{sf::Vector2f{0, 0}};
		auto object_size{sf::Vector2f{size}};
		for(auto y{size_t{0}}; y < objects_.size(); ++y) {
			object_size.y = size.y * (bounds_[y + 1] - bounds_[y]);
			objects_[y]->resize(object_size, position + coordinate);
			coordinate.y += object_size.y;
		}
	}
	
	auto BoxBorderVertical::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			auto position{sf::Vector2f{pointer.position.x - layout_.position.x, pointer.position.y - layout_.position.y}};
			if(position.x < 0.0f || position.x > layout_.size.x || position.y < 0.0f || position.y > layout_.size.y) {
				return false;
			}
			position.y = position.y / layout_.size.y;
			
			auto i{size_t{1}};
			while(position.y > bounds_[i]) {
				++i;
			}
			return objects_[i - 1]->handle_event(event);
		}).some_or_else([=] {
			bool updated{false};
			for(auto& object: objects_) {
				if(object->handle_event(event)) {
					updated = true;
				}
			}
			return updated;
		});
	}
	
	auto BoxBorderVertical::get_min_size() const -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		auto object_min_sizes{std::vector<sf::Vector2f>{objects_.size()}};
		for(auto i{size_t{0}}; i < object_min_sizes.size(); ++i) {
			object_min_sizes[i] = objects_[i]->get_min_size();
		}
		
		for(auto i{size_t{0}}; i < object_min_sizes.size(); ++i) {
			auto object_min_size{sf::Vector2f{object_min_sizes[i].x, object_min_sizes[i].y / (bounds_[i + 1] - bounds_[i])}};
			min_size = max(object_min_size, min_size);
		}
		
		return max(min_size, this->minimum_size_);
	}
	
	auto BoxBorderVertical::get_normal_size() const -> sf::Vector2f {
		auto normal_size{sf::Vector2f{0, 0}};
		auto object_normal_sizes{std::vector<sf::Vector2f>{objects_.size()}};
		for(auto i{size_t{0}}; i < object_normal_sizes.size(); ++i) {
			object_normal_sizes[i] = objects_[i]->get_normal_size();
		}
		
		for(auto i{size_t{0}}; i < object_normal_sizes.size(); ++i) {
			auto object_normal_size{sf::Vector2f{object_normal_sizes[i].x, object_normal_sizes[i].y / (bounds_[i + 1] - bounds_[i])}};
			normal_size = max(object_normal_size, normal_size);
		}
		
		return normal_size;
	}
	
	auto BoxBorderVertical::get_array_size() const -> size_t {
		return objects_.size();
	}
	
	auto BoxBorderVertical::get_object_at(size_t index) -> IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxBorderVertical::get_object_at(size_t index) const -> IScalable const& {
		return *objects_.at(index);
	}
	
	auto BoxBorderVertical::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& object: objects_) {
			object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		}
	}
}

auto ieml::Decode<char, ie::BoxBorderVertical::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxBorderVertical::Make> {
	auto map{node.get_map_view().except()};
	auto min_size{map.get_as<sf::Vector2f>("min-size").except().ok_or({})};
	auto two_objects{map.at("first-object").ok_or_none() && map.at("second-object").ok_or_none()};
	for(auto& [first_object, second_object]: two_objects) {
		return ie::BoxBorderVertical::Make{
			first_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			second_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			map.get_as<float>("bound").except().ok_or(0.5),
			min_size
		};
	}
	auto objects{map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except()};
	for(auto bounds: map.at("bounds").ok_or_none()) {
		return ie::BoxBorderVertical::Make{std::move(objects), bounds.as<std::vector<float> >().except(), min_size};
	}
	return {{std::move(objects), min_size}};
}
