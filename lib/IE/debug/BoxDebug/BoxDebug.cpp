#include "BoxDebug.hpp"
#include <cmath>

namespace ie {
	BoxDebug::Make::Make(BoxPtr<IScalable::Make>&& object) :
		object(std::move(object)) {
	}
	
	BoxDebug* BoxDebug::Make::make(InitInfo init_info) {
		return new BoxDebug{std::move(*this), init_info};
	}
	
	BoxDebug::BoxDebug(Make&& make, InitInfo init_info) :
		Box({}),
		object(make.object->make(init_info)),
		render_target(&init_info.render_target),
		active(false),
		drawn(false) {
		init_info.draw_manager.add(*this);
	}
	
	BoxDebug::BoxDebug(BoxPtr<IScalable>&& object) :
		Box({}), object(std::move(object)), render_target(nullptr), active(false), drawn(false) {
	}
	
	void BoxDebug::init(InitInfo init_info) {
		object->init(init_info);
		init_info.draw_manager.add(*this);
		this->render_target = &init_info.render_target;
	}
	
	void BoxDebug::draw() {
		drawn = true;
		object->draw_debug(*render_target, 0, 2, 0, 72);
	}
	
	void BoxDebug::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		object->resize(size, position);
	}
	
	bool BoxDebug::update_interactions(sf::Vector2f mouse_position) {
		active = true;
		return object->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxDebug::get_min_size() const {
		return object->get_min_size();
	}
	
	sf::Vector2f BoxDebug::get_normal_size() const {
		return object->get_normal_size();
	}
	
	IScalable& BoxDebug::get_object() {
		return *object;
	}
	
	const IScalable& BoxDebug::get_object() const {
		return *object;
	}
	
	BoxDebug* BoxDebug::copy() {
		return new BoxDebug{*this};
	}
	
	void BoxDebug::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		sf::Vector2f size{this->get_area_size() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2, indent * 2})};
		size = {std::round(size.x - 2.0f), std::round(size.y - 2.0f)};
		sf::Vector2f position{this->get_area_position() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
		position = {std::round(position.x + 1.0f), std::round(position.y + 1.0f)};
		
		if(drawn || active) {
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			
			if(drawn && active) {
				rectangle.setFillColor(sf::Color(0, 255, 0, 60));
			} else if(drawn) {
				rectangle.setFillColor(sf::Color(255, 255, 0, 60));
			} else if(active) {
				rectangle.setFillColor(sf::Color(255, 0, 0, 60));
			}
			
			render_target.draw(rectangle);
		}
		
		active = false;
		drawn = false;
		
		object->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	bool DecodePointer<BoxDebug>::decode_pointer(const YAML::Node& node, BoxDebug*& box_debug) {
		box_debug = new BoxDebug{node["object"].as<BoxPtr<IScalable> >()};
		return true;
	}
}