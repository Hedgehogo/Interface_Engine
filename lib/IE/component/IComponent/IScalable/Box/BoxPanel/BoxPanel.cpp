#include "BoxPanel.hpp"

namespace ie {
	BoxPanel::Make::Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		panel(std::move(panel)), object(std::move(object)), min_size(min_size) {
	}
	
	BoxPanel* BoxPanel::Make::make(InitInfo init_info) {
		return new BoxPanel{std::move(*this), init_info};
	}
	
	BoxPanel::BoxPanel(Make&& make, InitInfo init_info) :
		Box(make.min_size), object(make.object->make(init_info)), panel(make.panel->make(init_info)) {
	}
	
	BoxPanel::BoxPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f min_size) :
		Box(min_size), object(std::move(object)), panel(std::move(panel)) {
	}
	
	void BoxPanel::init(InitInfo init_info) {
		object->init(init_info);
		panel->init(init_info);
	}
	
	void BoxPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f BoxPanel::get_min_size() const {
		return max(object->get_min_size(), panel->get_min_size(), minimum_size);
	}
	
	sf::Vector2f BoxPanel::get_normal_size() const {
		return max(object->get_normal_size(), panel->get_normal_size());
	}
	
	IScalable& BoxPanel::get_object() {
		return *object;
	}
	
	const IScalable& BoxPanel::get_object() const {
		return *object;
	}
	
	const ConstPanel& BoxPanel::get_panel() const {
		return *panel;
	}
	
	BoxPanel* BoxPanel::copy() {
		return new BoxPanel{*this};
	}
	
	void BoxPanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		object->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		panel->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
	
	bool DecodePointer<BoxPanel>::decode_pointer(const YAML::Node& node, BoxPanel*& box_with_panel) {
		box_with_panel = new BoxPanel{
			node["panel"].as<BoxPtr<ConstPanel> >(),
			node["panel"].as<BoxPtr<IScalable> >(),
			conv_def(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}