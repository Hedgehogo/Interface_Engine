#include "BoxTabs.hpp"

#include <utility>

namespace ie {
	BoxTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISRSize> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::move(value)), min_size(min_size) {
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
		value_(make.value.make(init_info.dyn_buffer)) {
		value_.set_upper_bound(objects_.size() - 1);
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
		draw_managers_[value_.get()].draw();
	}
	
	bool BoxTabs::update_interactions(sf::Vector2f mouse_position) {
		return objects_[value_.get()]->update_interactions(mouse_position);
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
}

orl::Option<ie::BoxTabs::Make> ieml::Decode<char, ie::BoxTabs::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxTabs::Make{
		map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISRSize> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
