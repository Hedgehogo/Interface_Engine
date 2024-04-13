#include "BoxBorderHorizontal.hpp"
#include <vector>

namespace ie {
	BoxBorderHorizontal::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(std::move(add_bounds(bounds))), min_size(min_size) {
	}
	
	BoxBorderHorizontal::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(gen_bounds(this->objects.size())), min_size(min_size) {
	}
	
	BoxBorderHorizontal::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		float bound,
		sf::Vector2f min_size
	) :
		objects(make_vector(std::move(first_object), std::move(second_object))), bounds({0.f, bound, 1.f}), min_size(min_size) {
	}
	
	BoxBorderHorizontal* BoxBorderHorizontal::Make::make(InitInfo init_info) {
		return new BoxBorderHorizontal{std::move(*this), init_info};
	}
	
	BoxBorderHorizontal::BoxBorderHorizontal(Make&& make, InitInfo init_info) :
		Box(make.min_size), objects_(map_make(std::move(make.objects), init_info)), bounds_(std::move(make.bounds)) {
	}
	
	auto BoxBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		auto coordinate{sf::Vector2f{0, 0}};
		auto object_size{size};
		for(auto x{size_t{0}}; x < objects_.size(); ++x) {
			object_size.x = size.x * (bounds_[x + 1] - bounds_[x]);
			objects_[x]->resize(object_size, position + coordinate);
			coordinate.x += object_size.x;
		}
	}
	
	auto BoxBorderHorizontal::update_interactions(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			auto position{sf::Vector2f{touch.position.x - layout_.position.x, touch.position.y - layout_.position.y}};
			if(position.x < 0.0f || position.x > layout_.size.x || position.y < 0.0f || position.y > layout_.size.y) {
				return false;
			}
			position.x = position.x / layout_.size.x;
			
			auto object{size_t{1}};
			while(position.x > bounds_[object]) {
				++object;
			}
			return objects_[object - 1]->update_interactions(event);
		}).some_or_else([=] {
			bool updated{false};
			for(auto& object: objects_) {
				if(object->update_interactions(event)) {
					updated = true;
				}
			}
			return updated;
		});
	}
	
	auto BoxBorderHorizontal::get_min_size() const -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		auto object_min_sizes{std::vector<sf::Vector2f>{objects_.size()}};
		for(auto i{size_t{0}}; i < object_min_sizes.size(); ++i) {
			object_min_sizes[i] = objects_[i]->get_min_size();
		}
		
		for(auto i{size_t{0}}; i < object_min_sizes.size(); ++i) {
			auto object_min_size{sf::Vector2f{object_min_sizes[i].x / (bounds_[i + 1] - bounds_[i]), object_min_sizes[i].y}};
			min_size = max(object_min_size, min_size);
		}
		
		return max(min_size, this->minimum_size_);
	}
	
	auto BoxBorderHorizontal::get_normal_size() const -> sf::Vector2f {
		auto normal_size{sf::Vector2f{0, 0}};
		auto object_normal_sizes{std::vector<sf::Vector2f>{objects_.size()}};
		for(auto i{size_t{0}}; i < object_normal_sizes.size(); ++i) {
			object_normal_sizes[i] = objects_[i]->get_normal_size();
		}
		
		for(auto i{size_t{0}}; i < object_normal_sizes.size(); ++i) {
			auto object_normal_size{sf::Vector2f{object_normal_sizes[i].x / (bounds_[i + 1] - bounds_[i]), object_normal_sizes[i].y}};
			normal_size = max(object_normal_size, normal_size);
		}
		
		return normal_size;
	}
	
	auto BoxBorderHorizontal::get_array_size() const -> size_t {
		return objects_.size();
	}
	
	auto BoxBorderHorizontal::get_object_at(size_t index) -> IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxBorderHorizontal::get_object_at(size_t index) const -> IScalable const& {
		return *objects_.at(index);
	}
	
	auto BoxBorderHorizontal::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& object: objects_) {
			object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		}
	}
}

auto ieml::Decode<char, ie::BoxBorderHorizontal::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxBorderHorizontal::Make> {
	auto map{node.get_map_view().except()};
	auto min_size{map.get_as<sf::Vector2f>("min-size").except().ok_or({})};
	auto two_objects{map.at("first-object").ok_or_none() && map.at("second-object").ok_or_none()};
	for(auto& [first_object, second_object]: two_objects) {
		return ie::BoxBorderHorizontal::Make{
			first_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			second_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			map.get_as<float>("bound").except().ok_or(0.5),
			min_size
		};
	}
	auto objects{map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except()};
	for(auto& bounds: map.at("bounds").ok_or_none()) {
		return ie::BoxBorderHorizontal::Make{
			std::move(objects),
			bounds.as<std::vector<float> >().except(),
			min_size
		};
	}
	return {{std::move(objects), min_size}};
}
