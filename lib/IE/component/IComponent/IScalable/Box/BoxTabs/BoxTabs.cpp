#include "BoxTabs.hpp"

#include <utility>

namespace ie {
	BoxTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(value), min_size(min_size) {
	}
	
	BoxTabs* BoxTabs::Make::make(InitInfo init_info) {
		return new BoxTabs{std::move(*this), init_info};
	}
	
	BoxTabs::BoxTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		draw_managers_(make.objects.size()),
		objects_(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers_[i]);
		})),
		value_(make.value) {
		init_info.draw_manager.add(*this);
	}
	
	BoxTabs::BoxTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f min_size) :
		Box(min_size), draw_managers_(objects.size()), objects_(std::move(objects)), value_(std::move(value)) {
	}
	
	BoxTabs::BoxTabs(const BoxTabs& other) :
		Box(other), draw_managers_(other.objects_.size()), objects_(other.objects_), value_(other.value_) {
	}
	
	void BoxTabs::init(InitInfo init_info) {
		for(size_t i = 0; i < objects_.size(); ++i) {
			objects_[i]->init(init_info.copy(draw_managers_[i]));
		}
		init_info.draw_manager.add(*this);
	}
	
	void BoxTabs::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		for(auto& object: objects_) {
			object->set_position(position);
		}
	}
	
	void BoxTabs::move(sf::Vector2f position) {
		layout_.move(position);
		for(auto& object: objects_) {
			object->move(position);
		}
	}
	
	void BoxTabs::set_size(sf::Vector2f size) {
		layout_.set_size(size);
		for(auto& object: objects_) {
			object->set_size(size);
		}
	}
	
	void BoxTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		for(auto& object: objects_) {
			object->resize(size, position);
		}
	}
	
	void BoxTabs::draw() {
		draw_managers_[value_->get_value()].draw();
	}
	
	bool BoxTabs::update_interactions(sf::Vector2f mouse_position) {
		return objects_[value_->get_value()]->update_interactions(mouse_position);
	}
	
	size_t BoxTabs::get_array_size() const {
		return objects_.size();
	}
	
	IScalable& BoxTabs::get_object_at(size_t index) {
		return *objects_.at(index);
	}
	
	const IScalable& BoxTabs::get_object_at(size_t index) const {
		return *objects_.at(index);
	}
	
	BoxTabs* BoxTabs::copy() {
		return new BoxTabs{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxTabs>::decode_pointer(const YAML::Node& node, BoxTabs*& box_with_tabs) {
		box_with_tabs = new BoxTabs{
			node["objects"].as<std::vector<BoxPtr<IScalable> > >(),
			Buffer::get<ISint>(node["value"]),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;

	}
	*/
}