#include "BoxPanel.hpp"

namespace ie {
	BoxPanel::Make::Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		panel(std::move(panel)), object(std::move(object)), min_size(min_size) {
	}
	
	auto BoxPanel::Make::make(InitInfo init_info) -> BoxPanel* {
		return new BoxPanel{std::move(*this), init_info};
	}
	
	BoxPanel::BoxPanel(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)), panel_(make.panel->make(init_info)) {
	}
	
	auto BoxPanel::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		IComponentObject::resize(size, position);
		panel_->resize(size, position);
	}
	
	auto BoxPanel::get_min_size() const -> sf::Vector2f {
		return max(object_->get_min_size(), panel_->get_min_size(), minimum_size_);
	}
	
	auto BoxPanel::get_normal_size() const -> sf::Vector2f {
		return max(object_->get_normal_size(), panel_->get_normal_size());
	}
	
	auto BoxPanel::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxPanel::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxPanel::get_panel() const -> ConstPanel const& {
		return *panel_;
	}
	
	auto BoxPanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		panel_->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxPanel::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxPanel::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxPanel::Make{
		map.at("panel").except().as<ie::BoxPtr<ie::ConstPanel::Make> >().except(),
		map.at("panel").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
