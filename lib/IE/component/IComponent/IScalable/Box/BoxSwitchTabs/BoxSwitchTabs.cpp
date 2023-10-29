#include "BoxSwitchTabs.hpp"

namespace ie {
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<size_t> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(value), min_size(min_size) {
	}
	
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, size_t index, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::make_shared<SValue<size_t> >(index)), min_size(min_size) {
	}
	
	BoxSwitchTabs* BoxSwitchTabs::Make::make(InitInfo init_info) {
		return new BoxSwitchTabs{std::move(*this), init_info};
	}
	
	BoxSwitchTabs::BoxSwitchTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size), draw_managers_(make.objects.size()),
		objects_(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers_[i]);
		})), value_(make.value) {
		init_info.draw_manager.add(*this);
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, PSValue<size_t> value, sf::Vector2f min_size) :
		Box(min_size), draw_managers_(objects.size()), objects_(std::move(objects)), value_(value) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, size_t index, sf::Vector2f min_size) :
		Box(min_size), draw_managers_(objects.size()), objects_(std::move(objects)), value_(std::make_shared<SValue<size_t>>(index)) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(const BoxSwitchTabs& other) :
		Box(other), draw_managers_(other.objects_.size()), objects_(other.objects_), value_(other.value_) {
	}
	
	void BoxSwitchTabs::init(InitInfo init_info) {
		init_info.draw_manager.add(*this);
		
		for(size_t i = 0; i < objects_.size(); ++i) {
			objects_[i]->init(init_info.copy(draw_managers_[i]));
		}
	}
	
	void BoxSwitchTabs::set_value(std::shared_ptr<SValue<size_t>> index) {
		value_ = index;
	}
	
	std::shared_ptr<SValue<size_t>> BoxSwitchTabs::get_value() {
		return value_;
	}
	
	void BoxSwitchTabs::set_index(size_t index) {
		value_->set_value(index);
	}
	
	size_t BoxSwitchTabs::get_index() {
		return value_->get_value();
	}
	
	void BoxSwitchTabs::draw() {
		draw_managers_[value_->get_value()].draw();
	}
	
	void BoxSwitchTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		for(auto& object : objects_) {
			object->resize(size, position);
		}
	}
	
	bool BoxSwitchTabs::update_interactions(sf::Vector2f mouse_position) {
		return objects_[value_->get_value()]->update_interactions(mouse_position);
	}
	
	size_t BoxSwitchTabs::get_array_size() const {
		return objects_.size();
	}
	
	IScalable& BoxSwitchTabs::get_object_at(size_t index) {
		return *objects_.at(index);
	}
	
	const IScalable& BoxSwitchTabs::get_object_at(size_t index) const {
		return *objects_.at(index);
	}
	
	BoxSwitchTabs* BoxSwitchTabs::copy() {
		return new BoxSwitchTabs{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxSwitchTabs>::decode_pointer(const YAML::Node& node, BoxSwitchTabs*& box_with_changeable_objects) {
		auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
		auto min_size{conv_def(node["min-size"], sf::Vector2f{})};
		
		if(node["value"]) {
			box_with_changeable_objects = new BoxSwitchTabs{
				std::move(objects),
				Buffer::get<SValue<size_t>>(node["value"]),
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
	*/
	
	void BoxSwitchTabs::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		objects_[value_->get_value()]->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}