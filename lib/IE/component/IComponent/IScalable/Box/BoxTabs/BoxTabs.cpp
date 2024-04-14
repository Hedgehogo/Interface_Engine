#include "BoxTabs.hpp"

#include <utility>

namespace ie {
	BoxTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISRSize> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::move(value)), min_size(min_size) {
	}
	
	auto BoxTabs::Make::make(InitInfo init_info) -> BoxTabs* {
		return new BoxTabs{std::move(*this), init_info};
	}
	
	BoxTabs::BoxTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		draw_managers_(make.objects.size()),
		objects_(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers_[i]);
		})),
		value_(make.value.make(SInitInfo{init_info})) {
		value_.set_upper_bound(objects_.size() - 1);
		init_info.draw_manager.add(*this);
	}
	
	auto BoxTabs::set_position(sf::Vector2f position) -> void {
		layout_.set_position(position);
		for(auto& object: objects_) {
			object->set_position(position);
		}
	}
	
	auto BoxTabs::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		for(auto& object: objects_) {
			object->move(offset);
		}
	}
	
	auto BoxTabs::set_size(sf::Vector2f size) -> void {
		layout_.set_size(size);
		for(auto& object: objects_) {
			object->set_size(size);
		}
	}
	
	auto BoxTabs::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		for(auto& object: objects_) {
			object->resize(size, position);
		}
	}
	
	auto BoxTabs::draw() -> void {
		draw_managers_[value_.get()].draw();
	}
	
	auto BoxTabs::update_interactions(Event event) -> bool {
		return objects_[value_.get()]->update_interactions(event);
	}
	
	auto BoxTabs::get_array_size() const -> size_t {
		return objects_.size();
	}
	
	auto BoxTabs::get_object_at(size_t index) -> IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxTabs::get_object_at(size_t index) const -> IScalable const& {
		return *objects_.at(index);
	}
}

auto ieml::Decode<char, ie::BoxTabs::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxTabs::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxTabs::Make{
		map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISRSize> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
