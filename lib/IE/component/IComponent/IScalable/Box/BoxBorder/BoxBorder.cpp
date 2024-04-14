#include "BoxBorder.hpp"
#include <vector>

namespace ie {
	BoxBorder::Make::Make(
		std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects,
		std::vector<float> bounds_horizontal,
		std::vector<float> bounds_vertical,
		sf::Vector2f min_size
	) :
		objects(std::move(objects)),
		bounds_horizontal(std::move(add_bounds(bounds_horizontal))),
		bounds_vertical(std::move(add_bounds(bounds_vertical))),
		min_size(min_size) {
	}
	
	BoxBorder::Make::Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f min_size) :
		objects(std::move(objects)),
		bounds_horizontal(gen_bounds(this->objects.size())),
		bounds_vertical(gen_bounds(y_size(this->objects))),
		min_size(min_size) {
	}
	
	auto BoxBorder::Make::make(InitInfo init_info) -> BoxBorder* {
		return new BoxBorder{std::move(*this), init_info};
	}
	
	BoxBorder::BoxBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		objects_(map_make(std::move(make.objects), init_info)),
		bounds_horizontal_(std::move(make.bounds_horizontal)),
		bounds_vertical_(std::move(make.bounds_vertical)) {
	}
	
	auto BoxBorder::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		auto coordinate{sf::Vector2f{}};
		auto object_size{size};
		for(auto x{size_t{0}}; x < objects_.size(); ++x) {
			object_size.x = size.x * (bounds_horizontal_[x + 1] - bounds_horizontal_[x]);
			coordinate.y = 0;
			for(auto y{size_t{0}}; y < objects_[0].size(); ++y) {
				object_size.y = size.y * (bounds_vertical_[y + 1] - bounds_vertical_[y]);
				objects_[x][y]->resize(object_size, position + coordinate);
				coordinate.y += object_size.y;
			}
			coordinate.x += object_size.x;
		}
	}
	
	auto BoxBorder::handle_event(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			auto position{sf::Vector2f{touch.position.x - layout_.position.x, touch.position.y - layout_.position.y}};
			if(position.x < 0.0f || position.x > layout_.size.x || position.y < 0.0f || position.y > layout_.size.y) {
				return false;
			}
			position = {position.x / layout_.size.x, position.y / layout_.size.y};
			
			auto object{sf::Vector2u{1, 1}};
			while(position.x > bounds_horizontal_[object.x]) {
				++object.x;
			}
			while(position.y > bounds_vertical_[object.y]) {
				++object.y;
			}
			return objects_[object.x - 1][object.y - 1]->handle_event(event);
		}).some_or_else([=] {
			bool updated{false};
			for(auto& line: objects_) {
				for(auto& object: line) {
					if(object->handle_event(event)) {
						updated = true;
					}
				}
			}
			return updated;
		});
	}
	
	auto BoxBorder::get_min_size() const -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		auto object_min_sizes{std::vector<std::vector<sf::Vector2f> >{objects_.size()}};
		for(auto x{size_t{0}}; x < object_min_sizes.size(); ++x) {
			for(auto y{size_t{0}}; y < object_min_sizes[x].size(); ++y) {
				object_min_sizes[x][y] = objects_[x][y]->get_min_size();
			}
		}
		
		auto line_min_size{sf::Vector2f{0, 0}};
		auto object_min_size{sf::Vector2f{0, 0}};
		for(auto& line: object_min_sizes) {
			line_min_size.y = 0;
			for(auto y{size_t{0}}; y < line.size(); ++y) {
				object_min_size.y = line[y].y / (bounds_vertical_[y + 1] - bounds_vertical_[y]);
				line_min_size.y = std::max(object_min_size.y, line_min_size.y);
			}
			min_size.y = std::max(line_min_size.y, min_size.y);
		}
		
		for(auto y{size_t{0}}; y < object_min_sizes[0].size(); ++y) {
			line_min_size.x = 0;
			for(auto x{size_t{0}}; x < object_min_sizes.size(); ++x) {
				object_min_size.x = object_min_sizes[x][y].x / (bounds_horizontal_[x + 1] - bounds_horizontal_[x]);
				line_min_size.x = std::max(object_min_size.x, line_min_size.x);
			}
			min_size.x = std::max(line_min_size.x, min_size.x);
		}
		
		return {std::max(min_size.x, this->minimum_size_.x), std::max(min_size.y, this->minimum_size_.y)};
	}
	
	auto BoxBorder::get_normal_size() const -> sf::Vector2f {
		auto normal_size{sf::Vector2f{0, 0}};
		auto object_normal_sizes{std::vector<std::vector<sf::Vector2f> >{objects_.size()}};
		for(auto x{size_t{0}}; x < object_normal_sizes.size(); ++x) {
			for(auto y{size_t{0}}; y < object_normal_sizes[x].size(); ++y) {
				object_normal_sizes[x][y] = objects_[x][y]->get_normal_size();
			}
		}
		
		auto line_normal_size{sf::Vector2f{0, 0}};
		auto object_normal_size{sf::Vector2f{0, 0}};
		for(auto& line: object_normal_sizes) {
			line_normal_size.y = 0;
			for(auto y{size_t{0}}; y < line.size(); ++y) {
				object_normal_size.y = line[y].y / (bounds_vertical_[y + 1] - bounds_vertical_[y]);
				line_normal_size.y = std::max(object_normal_size.y, line_normal_size.y);
			}
			normal_size.y = std::max(line_normal_size.y, normal_size.y);
		}
		
		for(auto y{size_t{0}}; y < object_normal_sizes[0].size(); ++y) {
			line_normal_size.x = 0;
			for(auto x{size_t{0}}; x < object_normal_sizes.size(); ++x) {
				object_normal_size.x = object_normal_sizes[x][y].x / (bounds_horizontal_[x + 1] - bounds_horizontal_[x]);
				line_normal_size.x = std::max(object_normal_size.x, line_normal_size.x);
			}
			normal_size.x = std::max(line_normal_size.x, normal_size.x);
		}
		
		return normal_size;
	}
	
	auto BoxBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& line: objects_) {
			for(auto& object: line) {
				object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
			}
		}
	}
}

auto ieml::Decode<char, ie::BoxBorder::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxBorder::Make> {
	auto map{node.get_map_view().except()};
	auto objects(map.at("objects").except().as<std::vector<std::vector<ie::BoxPtr<ie::IScalable::Make> > > >().except());
	auto min_size{map.get_as<sf::Vector2f>("min-size").except().ok_or({})};
	auto bounds_vertical{map.at("bounds-vertical")};
	auto bounds_horizontal{map.at("bounds-horizontal")};
	if(bounds_vertical.is_ok() && bounds_horizontal.is_ok()) {
		return ie::BoxBorder::Make{
			std::move(objects),
			bounds_vertical.ok().as<std::vector<float> >().except(),
			bounds_horizontal.ok().as<std::vector<float> >().except(),
			min_size
		};
	}
	return {{std::move(objects), min_size}};
}
