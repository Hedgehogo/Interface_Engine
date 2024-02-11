#include "BoxSwitchTabs.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"

namespace ie {
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISMRSize> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::move(value)), min_size(min_size) {
	}
	
	BoxSwitchTabs* BoxSwitchTabs::Make::make(InitInfo init_info) {
		return new BoxSwitchTabs{std::move(*this), init_info};
	}
	
	BoxSwitchTabs::BoxSwitchTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size), draw_managers_(make.objects.size()),
		objects_(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers_[i]);
		})), value_(make.value.make(init_info.dyn_buffer)) {
		value_.set_bounds(0, objects_.size() - 1);
		init_info.draw_manager.add(*this);
	}
	
	ISMRSize& BoxSwitchTabs::get_value() {
		return value_;
	}
	
	void BoxSwitchTabs::set_index(size_t index) {
		value_.set(index);
	}
	
	size_t BoxSwitchTabs::get_index() {
		return value_.get();
	}
	
	void BoxSwitchTabs::draw() {
		draw_managers_[value_.get()].draw();
	}
	
	void BoxSwitchTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		for(auto& object: objects_) {
			object->resize(size, position);
		}
	}
	
	bool BoxSwitchTabs::update_interactions(sf::Vector2f mouse_position) {
		return objects_[value_.get()]->update_interactions(mouse_position);
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
	
	void BoxSwitchTabs::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		objects_[value_.get()]->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}

orl::Option<ie::BoxSwitchTabs::Make> ieml::Decode<char, ie::BoxSwitchTabs::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxSwitchTabs::Make{
		map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except(),
		map.get_as<ie::MakeDyn<ie::ISMRSize> >("value").ok_or_else([] {
			return ie::MakeDyn<ie::ISMRSize>{ie::make_box_ptr<ie::SMRSize::Make>(0u)};
		}),
		map.get_as<sf::Vector2f>("min-size").ok_or({})
	};
}
