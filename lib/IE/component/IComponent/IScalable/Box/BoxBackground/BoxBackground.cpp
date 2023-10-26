#include "BoxBackground.hpp"

namespace ie {
	BoxBackground::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset, sf::Vector2f min_size) :
		object(std::move(object)), background(std::move(background)), offset(offset), min_size(min_size) {
	}
	
	BoxBackground* BoxBackground::Make::make(InitInfo init_info) {
		return new BoxBackground{std::move(*this), init_info};
	}
	
	BoxBackground::BoxBackground(Make&& make, InitInfo init_info) :
		Box(make.min_size), background(make.background->make(init_info)), object(make.object->make(init_info)), offset(make.offset) {
	}
	
	BoxBackground::BoxBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset, sf::Vector2f min_size) :
		Box(min_size), background(std::move(background)), object(std::move(object)), offset(offset) {
	}
	
	void BoxBackground::init(InitInfo init_info) {
		background->init(init_info);
		object->init(init_info);
	}
	
	void BoxBackground::set_position(sf::Vector2f position) {
		layout.set_position(position);
		background->set_position(position);
		object->set_position(position);
	}
	
	void BoxBackground::move(sf::Vector2f position) {
		layout.move(position);
		background->move(position);
		object->move(position);
	}
	
	void BoxBackground::set_size(sf::Vector2f size) {
		layout.set_size(size);
		background->set_size(size);
		object->set_size(size);
	}
	
	sf::Vector2f BoxBackground::get_min_size() const {
		return max(object->get_min_size() + offset * 2.f, background->get_min_size(), minimum_size);
	}
	
	sf::Vector2f BoxBackground::get_normal_size() const {
		return max(object->get_normal_size() + offset * 2.f, background->get_normal_size());
	}
	
	IUninteractive& BoxBackground::get_background() {
		return *background;
	}
	
	const IUninteractive& BoxBackground::get_background() const {
		return *background;
	}
	
	IScalable& BoxBackground::get_object() {
		return *object;
	}
	
	const IScalable& BoxBackground::get_object() const {
		return *object;
	}
	
	void BoxBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		background->resize(size, position);
		object->resize(size - offset * 2.f, position + offset);
	}
	
	bool BoxBackground::update_interactions(sf::Vector2f mouse_position) {
		return object->update_interactions(mouse_position);
	}
	
	BoxBackground* BoxBackground::copy() {
		return new BoxBackground{*this};
	}
	
	void BoxBackground::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		
	}
	
	bool DecodePointer<BoxBackground>::decode_pointer(const YAML::Node& node, BoxBackground*& box_with_background) {
		box_with_background = new BoxBackground{
			node["object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IUninteractive> >(),
			conv_def(node["offset"], sf::Vector2f{}),
			conv_def(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}