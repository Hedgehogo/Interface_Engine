#include "BoxConstBezel.hpp"

namespace ie {
	BoxConstBezel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f min_size) :
		object(std::move(object)), bezel(std::move(bezel)), thickness(thickness), min_size(min_size) {
	}
	
	BoxConstBezel* BoxConstBezel::Make::make(InitInfo init_info) {
		return new BoxConstBezel{std::move(*this), init_info};
	}
	
	BoxConstBezel::BoxConstBezel(Make&& make, InitInfo init_info) :
		Box(make.min_size), bezel(make.bezel->make(init_info)), object(make.object->make(init_info)), thickness(make.thickness) {
	}
	
	BoxConstBezel::BoxConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f min_size) :
		Box(min_size), bezel(std::move(bezel)), object(std::move(object)), thickness(thickness) {
	}
	
	void BoxConstBezel::init(InitInfo init_info) {
		bezel->init(init_info);
		object->init(init_info);
	}
	
	void BoxConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool BoxConstBezel::update_interactions(sf::Vector2f mouse_position) {
		if(object->in_area(mouse_position)) {
			return object->update_interactions(mouse_position);
		}
		return bezel->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstBezel::get_min_size() const {
		return max(object->get_min_size() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->get_min_size(), minimum_size);
	}
	
	sf::Vector2f BoxConstBezel::get_normal_size() const {
		return max(object->get_normal_size() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->get_normal_size());
	}
	
	IScalable& BoxConstBezel::get_object() {
		return *object;
	}
	
	const IScalable& BoxConstBezel::get_object() const {
		return *object;
	}
	
	BoxConstBezel* BoxConstBezel::copy() {
		return new BoxConstBezel{*this};
	}
	
	void BoxConstBezel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		bezel->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object->draw_debug(render_target, indent, indent_addition, hue + hue_offset, hue_offset);
	}
	
	bool DecodePointer<BoxConstBezel>::decode_pointer(const YAML::Node& node, BoxConstBezel*& box_with_const_bezel) {
		box_with_const_bezel = new BoxConstBezel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["bezel"].as<BoxPtr<IUninteractive> >(),
			node["thickness"].as<float>(),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}

