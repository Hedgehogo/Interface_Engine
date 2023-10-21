#include "BoxSwitchTabs.hpp"

namespace ie {
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<uint> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(value), min_size(min_size) {
	}
	
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, uint index, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::make_shared<SValue<uint> >(index)), min_size(min_size) {
	}
	
	BoxSwitchTabs* BoxSwitchTabs::Make::make(InitInfo init_info) {
		return new BoxSwitchTabs{std::move(*this), init_info};
	}
	
	BoxSwitchTabs::BoxSwitchTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size), draw_managers(make.objects.size()),
		objects(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers[i]);
		})), value(make.value) {
		init_info.draw_manager.add(*this);
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, PSValue<uint> value, sf::Vector2f min_size) :
		Box(min_size), draw_managers(objects.size()), objects(std::move(objects)), value(value) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, uint index, sf::Vector2f min_size) :
		Box(min_size), draw_managers(objects.size()), objects(std::move(objects)), value(std::make_shared<SValue<uint>>(index)) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(const BoxSwitchTabs& other) :
		Box(other), draw_managers(other.objects.size()), objects(other.objects), value(other.value) {
	}
	
	void BoxSwitchTabs::init(InitInfo init_info) {
		init_info.draw_manager.add(*this);
		
		for(size_t i = 0; i < objects.size(); ++i) {
			objects[i]->init(init_info.copy(draw_managers[i]));
		}
	}
	
	void BoxSwitchTabs::set_value(std::shared_ptr<SValue<uint>> index) {
		value = index;
	}
	
	std::shared_ptr<SValue<uint>> BoxSwitchTabs::get_value() {
		return value;
	}
	
	void BoxSwitchTabs::set_index(uint index) {
		value->set_value(index);
	}
	
	uint BoxSwitchTabs::get_index() {
		return value->get_value();
	}
	
	void BoxSwitchTabs::draw() {
		draw_managers[value->get_value()].draw();
	}
	
	void BoxSwitchTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		for(auto& object : objects) {
			object->resize(size, position);
		}
	}
	
	bool BoxSwitchTabs::update_interactions(sf::Vector2f mouse_position) {
		return objects[value->get_value()]->update_interactions(mouse_position);
	}
	
	size_t BoxSwitchTabs::get_array_size() const {
		return objects.size();
	}
	
	IScalable& BoxSwitchTabs::get_object_at(size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxSwitchTabs::get_object_at(size_t index) const {
		return *objects.at(index);
	}
	
	BoxSwitchTabs* BoxSwitchTabs::copy() {
		return new BoxSwitchTabs{*this};
	}
	
	bool DecodePointer<BoxSwitchTabs>::decode_pointer(const YAML::Node& node, BoxSwitchTabs*& box_with_changeable_objects) {
		auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
		auto min_size{conv_def(node["min-size"], sf::Vector2f{})};
		
		if(node["value"]) {
			box_with_changeable_objects = new BoxSwitchTabs{
				std::move(objects),
				Buffer::get<SValue<uint>>(node["value"]),
				min_size
			};
		} else {
			box_with_changeable_objects = new BoxSwitchTabs{
				std::move(objects),
				conv_def(node["index"], 0u),
				min_size
			};
		}
		return true;
	}
	
	void BoxSwitchTabs::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		objects[value->get_value()]->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}