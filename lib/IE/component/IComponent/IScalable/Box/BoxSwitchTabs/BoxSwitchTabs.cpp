#include "BoxSwitchTabs.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"

namespace ie {
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISMRSize> value, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::move(value)), min_size(min_size) {
	}
	
	auto BoxSwitchTabs::Make::make(InitInfo init_info) -> BoxSwitchTabs* {
		return new BoxSwitchTabs{std::move(*this), init_info};
	}
	
	BoxSwitchTabs::BoxSwitchTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size), draw_managers_(make.objects.size()),
		objects_(map_make(std::move(make.objects), [&](size_t i) {
			return init_info.copy(draw_managers_[i]);
		})), value_(make.value.make(SInitInfo{init_info})) {
		value_.set_bounds(0, objects_.size() - 1);
		init_info.draw_manager.add(*this);
	}
	
	auto BoxSwitchTabs::get_value() -> ISMRSize& {
		return value_;
	}
	
	auto BoxSwitchTabs::set_index(size_t index) -> void {
		value_.set(index);
	}
	
	auto BoxSwitchTabs::get_index() -> size_t {
		return value_.get();
	}
	
	auto BoxSwitchTabs::draw() -> void {
		draw_managers_[value_.get()].draw();
	}
	
	auto BoxSwitchTabs::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		for(auto& object: objects_) {
			object->resize(size, position);
		}
	}
	
	auto BoxSwitchTabs::update_interactions(Event event) -> bool {
		return objects_[value_.get()]->update_interactions(event);
	}
	
	auto BoxSwitchTabs::get_array_size() const -> size_t {
		return objects_.size();
	}
	
	auto BoxSwitchTabs::get_object_at(size_t index) -> IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxSwitchTabs::get_object_at(size_t index) const -> const IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxSwitchTabs::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		objects_[value_.get()]->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxSwitchTabs::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitchTabs::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxSwitchTabs::Make{
		map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except(),
		map.get_as<ie::MakeDyn<ie::ISMRSize> >("value").except().ok_or_else([] {
			return ie::MakeDyn<ie::ISMRSize>{ie::make_box_ptr<ie::SMRSize::Make>(0u)};
		}),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
