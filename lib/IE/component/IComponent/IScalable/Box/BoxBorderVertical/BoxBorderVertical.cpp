#include "BoxBorderVertical.hpp"
#include <vector>

namespace ie {
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(std::move(add_bounds(bounds))), min_size(min_size) {
	}
	
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds(gen_bounds(this->objects.size())), min_size(min_size) {
	}
	
	BoxBorderVertical::Make::Make(BoxPtr<IScalable::Make>&& first_object, BoxPtr<IScalable::Make>&& second_object, float bound, sf::Vector2f min_size) :
		objects(make_vector(std::move(first_object), std::move(second_object))), bounds({0.f, bound, 1.f}), min_size(min_size) {
	}
	
	BoxBorderVertical* BoxBorderVertical::Make::make(InitInfo init_info) {
		return new BoxBorderVertical{std::move(*this), init_info};
	}
	
	BoxBorderVertical::BoxBorderVertical(Make&& make, InitInfo init_info) :
		Box(make.min_size), objects(map_make(std::move(make.objects), init_info)), bounds(std::move(make.bounds)) {
	}
	
	BoxBorderVertical::BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f min_size) :
		Box(min_size), objects(std::move(objects)), bounds(std::move(add_bounds(bounds))) {
	}
	
	BoxBorderVertical::BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f min_size) :
		Box(min_size), objects(std::move(objects)), bounds(gen_bounds(this->objects.size())) {
	}
	
	BoxBorderVertical::BoxBorderVertical(BoxPtr<IScalable>&& first_object, BoxPtr<IScalable>&& second_object, float bound, sf::Vector2f min_size) :
		Box(min_size), objects({std::move(first_object), std::move(second_object)}), bounds({0.f, bound, 1.f}) {
	}
	
	void BoxBorderVertical::init(InitInfo init_info) {
		for(auto& object: objects) {
			object->init(init_info);
		}
	}
	
	void BoxBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		sf::Vector2f coordinate{0, 0};
		sf::Vector2f object_size{size};
		for(size_t y = 0; y < objects.size(); ++y) {
			object_size.y = size.y * (bounds[y + 1] - bounds[y]);
			objects[y]->resize(object_size, position + coordinate);
			coordinate.y += object_size.y;
		}
	}
	
	bool BoxBorderVertical::update_interactions(sf::Vector2f mouse_position) {
		sf::Vector2f position{mouse_position.x - layout.position.x, mouse_position.y - layout.position.y};
		if(position.x < 0.0f || position.x > layout.size.x || position.y < 0.0f || position.y > layout.size.y)
			return false;
		position.y = position.y / layout.size.y;
		
		size_t i{1};
		while(position.y > bounds[i])
			++i;
		return objects[i - 1]->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxBorderVertical::get_min_size() const {
		sf::Vector2f min_size{0, 0};
		std::vector<sf::Vector2f> object_min_sizes(objects.size());
		for(size_t i = 0; i < object_min_sizes.size(); ++i) {
			object_min_sizes[i] = objects[i]->get_min_size();
		}
		
		sf::Vector2f object_min_size;
		for(size_t i = 0; i < object_min_sizes.size(); ++i) {
			object_min_size = {object_min_sizes[i].x, object_min_sizes[i].y / (bounds[i + 1] - bounds[i])};
			min_size = max(object_min_size, min_size);
		}
		
		return max(min_size, this->minimum_size);
	}
	
	sf::Vector2f BoxBorderVertical::get_normal_size() const {
		sf::Vector2f normal_size{0, 0};
		std::vector<sf::Vector2f> object_normal_sizes(objects.size());
		for(size_t i = 0; i < object_normal_sizes.size(); ++i) {
			object_normal_sizes[i] = objects[i]->get_normal_size();
		}
		
		sf::Vector2f object_normal_size;
		for(size_t i = 0; i < object_normal_sizes.size(); ++i) {
			object_normal_size = {object_normal_sizes[i].x, object_normal_sizes[i].y / (bounds[i + 1] - bounds[i])};
			normal_size = max(object_normal_size, normal_size);
		}
		
		return normal_size;
	}
	
	size_t BoxBorderVertical::get_array_size() const {
		return objects.size();
	}
	
	IScalable& BoxBorderVertical::get_object_at(size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxBorderVertical::get_object_at(size_t index) const {
		return *objects.at(index);
	}
	
	BoxBorderVertical* BoxBorderVertical::copy() {
		return new BoxBorderVertical{*this};
	}
	
	bool DecodePointer<BoxBorderVertical>::decode_pointer(const YAML::Node& node, BoxBorderVertical*& box_with_border_vertical) {
		auto min_size{conv_def(node["min-size"], sf::Vector2f{})};
		
		if(node["objects"]) {
			auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
			
			if(node["bounds"]) {
				box_with_border_vertical = new BoxBorderVertical{
					std::move(objects),
					node["bounds"].as<std::vector<float> >(),
					min_size
				};
			} else {
				box_with_border_vertical = new BoxBorderVertical{
					std::move(objects),
					min_size
				};
			}
		} else {
			box_with_border_vertical = new BoxBorderVertical{
				node["first-object"].as<BoxPtr<IScalable> >(),
				node["first-object"].as<BoxPtr<IScalable> >(),
				conv_def(node["bound"], 0.5f),
				min_size
			};
		}
		return true;
	}
	
	void BoxBorderVertical::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& object: objects) {
			object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		}
	}
}
