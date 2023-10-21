#include "BoxBorder.hpp"
#include <vector>

namespace ie {
	BoxBorder::Make::Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, std::vector<float> bounds_horizontal, std::vector<float> bounds_vertical, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds_horizontal(std::move(add_bounds(bounds_horizontal))), bounds_vertical(std::move(add_bounds(bounds_vertical))), min_size(min_size) {
	}
	
	BoxBorder::Make::Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f min_size) :
		objects(std::move(objects)), bounds_horizontal(gen_bounds(this->objects.size())), bounds_vertical(gen_bounds(y_size(this->objects))), min_size(min_size) {
	}
	
	BoxBorder* BoxBorder::Make::make(InitInfo init_info) {
		return new BoxBorder{std::move(*this), init_info};
	}
	
	BoxBorder::BoxBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		objects(map_make(std::move(make.objects), init_info)),
		bounds_horizontal(std::move(make.bounds_horizontal)),
		bounds_vertical(std::move(make.bounds_vertical)) {
	}
	
	BoxBorder::BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, std::vector<float> bounds_horizontal, std::vector<float> bounds_vertical, sf::Vector2f min_size) :
		Box(min_size), objects(std::move(objects)), bounds_horizontal(std::move(add_bounds(bounds_horizontal))), bounds_vertical(std::move(add_bounds(bounds_vertical))) {
	}
	
	BoxBorder::BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, sf::Vector2f min_size) :
		Box(min_size), objects(objects), bounds_horizontal(gen_bounds(this->objects.size())), bounds_vertical(gen_bounds(y_size(this->objects))) {
	}
	
	void BoxBorder::init(InitInfo init_info) {
		for(auto& line: objects) {
			for(auto& object: line) {
				object->init(init_info);
			}
		}
	}
	
	void BoxBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		sf::Vector2f coordinate{};
		sf::Vector2f object_size{size};
		for(size_t x = 0; x < objects.size(); ++x) {
			object_size.x = size.x * (bounds_horizontal[x + 1] - bounds_horizontal[x]);
			coordinate.y = 0;
			for(size_t y = 0; y < objects[0].size(); ++y) {
				object_size.y = size.y * (bounds_vertical[y + 1] - bounds_vertical[y]);
				objects[x][y]->resize(object_size, position + coordinate);
				coordinate.y += object_size.y;
			}
			coordinate.x += object_size.x;
		}
	}
	
	bool BoxBorder::update_interactions(sf::Vector2f mouse_position) {
		sf::Vector2f position{mouse_position.x - layout.position.x, mouse_position.y - layout.position.y};
		if(position.x < 0.0f || position.x > layout.size.x || position.y < 0.0f || position.y > layout.size.y) {
			return false;
		}
		position = {position.x / layout.size.x, position.y / layout.size.y};
		
		sf::Vector2u object{1, 1};
		while(position.x > bounds_horizontal[object.x]) {
			++object.x;
		}
		while(position.y > bounds_vertical[object.y]) {
			++object.y;
		}
		return objects[object.x - 1][object.y - 1]->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxBorder::get_min_size() const {
		sf::Vector2f min_size{0, 0};
		std::vector<std::vector<sf::Vector2f>> object_min_sizes(objects.size());
		for(size_t x = 0; x < object_min_sizes.size(); ++x) {
			for(size_t y = 0; y < object_min_sizes[x].size(); ++y) {
				object_min_sizes[x][y] = objects[x][y]->get_min_size();
			}
		}
		
		sf::Vector2f line_min_size{0, 0};
		sf::Vector2f object_min_size{0, 0};
		for(auto& line: object_min_sizes) {
			line_min_size.y = 0;
			for(size_t y = 0; y < line.size(); ++y) {
				object_min_size.y = line[y].y / (bounds_vertical[y + 1] - bounds_vertical[y]);
				line_min_size.y = std::max(object_min_size.y, line_min_size.y);
			}
			min_size.y = std::max(line_min_size.y, min_size.y);
		}
		
		for(size_t y = 0; y < object_min_sizes[0].size(); ++y) {
			line_min_size.x = 0;
			for(size_t x = 0; x < object_min_sizes.size(); ++x) {
				object_min_size.x = object_min_sizes[x][y].x / (bounds_horizontal[x + 1] - bounds_horizontal[x]);
				line_min_size.x = std::max(object_min_size.x, line_min_size.x);
			}
			min_size.x = std::max(line_min_size.x, min_size.x);
		}
		
		return {std::max(min_size.x, this->minimum_size.x), std::max(min_size.y, this->minimum_size.y)};
	}
	
	sf::Vector2f BoxBorder::get_normal_size() const {
		sf::Vector2f normal_size{0, 0};
		std::vector<std::vector<sf::Vector2f>> object_normal_sizes(objects.size());
		for(size_t x = 0; x < object_normal_sizes.size(); ++x) {
			for(size_t y = 0; y < object_normal_sizes[x].size(); ++y) {
				object_normal_sizes[x][y] = objects[x][y]->get_normal_size();
			}
		}
		
		sf::Vector2f line_normal_size{0, 0};
		sf::Vector2f object_normal_size{0, 0};
		for(auto& line: object_normal_sizes) {
			line_normal_size.y = 0;
			for(size_t y = 0; y < line.size(); ++y) {
				object_normal_size.y = line[y].y / (bounds_vertical[y + 1] - bounds_vertical[y]);
				line_normal_size.y = std::max(object_normal_size.y, line_normal_size.y);
			}
			normal_size.y = std::max(line_normal_size.y, normal_size.y);
		}
		
		for(size_t y = 0; y < object_normal_sizes[0].size(); ++y) {
			line_normal_size.x = 0;
			for(size_t x = 0; x < object_normal_sizes.size(); ++x) {
				object_normal_size.x = object_normal_sizes[x][y].x / (bounds_horizontal[x + 1] - bounds_horizontal[x]);
				line_normal_size.x = std::max(object_normal_size.x, line_normal_size.x);
			}
			normal_size.x = std::max(line_normal_size.x, normal_size.x);
		}
		
		return normal_size;
	}
	
	BoxBorder* BoxBorder::copy() {
		return new BoxBorder{*this};
	}
	
	void BoxBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(auto& line: objects) {
			for(auto& object: line) {
				object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
			}
		}
	}
	
	bool DecodePointer<BoxBorder>::decode_pointer(const YAML::Node& node, BoxBorder*& box_with_border) {
		auto objects(node["objects"].as<std::vector<std::vector<BoxPtr<IScalable> > > >());
		auto min_size{conv_def(node["min-size"], sf::Vector2f{})};
		
		if(node["bounds-vertical"] && node["bounds-horizontal"]) {
			box_with_border = new BoxBorder{
				std::move(objects),
				node["bounds-vertical"].as<std::vector<float> >(),
				node["bounds-horizontal"].as<std::vector<float> >(),
				min_size
			};
		} else {
			box_with_border = new BoxBorder{
				std::move(objects),
				min_size
			};
		}
		return true;
	}
}