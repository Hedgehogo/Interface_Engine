#include "BoxPanel.hpp"

namespace ie {
	BoxPanel::Make::Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		panel(std::move(panel)), object(std::move(object)), min_size(min_size) {
	}
	
	BoxPanel* BoxPanel::Make::make(InitInfo init_info) {
		return new BoxPanel{std::move(*this), init_info};
	}
	
	BoxPanel::BoxPanel(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)), panel_(make.panel->make(init_info)) {
	}
	
	void BoxPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
		panel_->resize(size, position);
	}
	
	sf::Vector2f BoxPanel::get_min_size() const {
		return max(object_->get_min_size(), panel_->get_min_size(), minimum_size_);
	}
	
	sf::Vector2f BoxPanel::get_normal_size() const {
		return max(object_->get_normal_size(), panel_->get_normal_size());
	}
	
	IScalable& BoxPanel::get_object() {
		return *object_;
	}
	
	const IScalable& BoxPanel::get_object() const {
		return *object_;
	}
	
	const ConstPanel& BoxPanel::get_panel() const {
		return *panel_;
	}
	
	void BoxPanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		panel_->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
}

orl::Option<ie::BoxPanel::Make> ieml::Decode<char, ie::BoxPanel::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxPanel::Make{
		map.at("panel").except().as<ie::BoxPtr<ie::ConstPanel::Make> >().move_except(),
		map.at("panel").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({}),
	};
}
