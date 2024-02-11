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
	
	void BoxBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		sf::Vector2f coordinate{0, 0};
		sf::Vector2f object_size{size};
		for(size_t x = 0; x < objects_.size(); ++x) {
			object_size.x = size.x * (bounds_[x + 1] - bounds_[x]);
			objects_[x]->resize(object_size, position + coordinate);
			coordinate.x += object_size.x;
		}
	}
	
	bool BoxBorderHorizontal::update_interactions(sf::Vector2f mouse_position) {
		sf::Vector2f position{mouse_position.x - layout_.position.x, mouse_position.y - layout_.position.y};
		if(position.x < 0.0f || position.x > layout_.size.x || position.y < 0.0f || position.y > layout_.size.y)
			return false;
		position.x = position.x / layout_.size.x;
		
		size_t object{1};
		while(position.x > bounds_[object])
			++object;
		return objects_[object - 1]->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxBorderHorizontal::get_min_size() const {
		sf::Vector2f min_size{0, 0};
		std::vector<sf::Vector2f> object_min_sizes(objects_.size());
		for(size_t i = 0; i < object_min_sizes.size(); ++i) {
			object_min_sizes[i] = objects_[i]->get_min_size();
		}
		
		sf::Vector2f object_min_size;
		for(size_t i = 0; i < object_min_sizes.size(); ++i) {
			object_min_size = {object_min_sizes[i].x / (bounds_[i + 1] - bounds_[i]), object_min_sizes[i].y};
			min_size = max(object_min_size, min_size);
		}
		
		return max(min_size, this->minimum_size_);
	}
	
	sf::Vector2f BoxBorderHorizontal::get_normal_size() const {
		sf::Vector2f normal_size{0, 0};
		std::vector<sf::Vector2f> object_normal_sizes(objects_.size());
		for(size_t i = 0; i < object_normal_sizes.size(); ++i) {
			object_normal_sizes[i] = objects_[i]->get_normal_size();
		}
		
		sf::Vector2f object_normal_size;
		for(size_t i = 0; i < object_normal_sizes.size(); ++i) {
			object_normal_size = {object_normal_sizes[i].x / (bounds_[i + 1] - bounds_[i]), object_normal_sizes[i].y};
			normal_size = max(object_normal_size, normal_size);
		}
		
		return normal_size;
	}
	
	size_t BoxBorderHorizontal::get_array_size() const {
		return objects_.size();
	}
	
	IScalable& BoxBorderHorizontal::get_object_at(size_t index) {
		return *objects_.at(index);
	}
	
	const IScalable& BoxBorderHorizontal::get_object_at(size_t index) const {
		return *objects_.at(index);
	}
	
	void BoxBorderHorizontal::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& object: objects_) {
			object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		}
	}
}

orl::Option<ie::BoxBorderHorizontal::Make> ieml::Decode<char, ie::BoxBorderHorizontal::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto min_size{map.get_as<sf::Vector2f>("min-size").ok_or({})};
	auto two_objects{map.at("first-object").ok_or_none() && map.at("second-object").ok_or_none()};
	for(auto& [first_object, second_object]: two_objects) {
		return ie::BoxBorderHorizontal::Make{
			first_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			second_object.as<ie::BoxPtr<ie::IScalable::Make> >().except(),
			map.get_as<float>("bound").ok_or(0.5),
			min_size
		};
	}
	auto objects{map.at("bounds").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except()};
	for(auto& bounds: map.at("bounds").ok_or_none()) {
		return ie::BoxBorderHorizontal::Make{
			std::move(objects),
			bounds.as<std::vector<float> >().except(),
			min_size
		};
	}
	return {{std::move(objects), min_size}};
}
