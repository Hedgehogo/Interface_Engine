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
		object_(make.object->make(init_info)),
		render_target_(&init_info.render_target),
		active_(false),
		drawn_(false) {
		init_info.draw_manager.add(*this);
	}
	
	BoxDebug::BoxDebug(BoxPtr<IScalable>&& object) :
		Box({}), object_(std::move(object)), render_target_(nullptr), active_(false), drawn_(false) {
	}
	
	void BoxDebug::draw() {
		drawn_ = true;
		object_->draw_debug(*render_target_, 0, 2, 0, 72);
	}
	
	void BoxDebug::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	bool BoxDebug::update_interactions(sf::Vector2f mouse_position) {
		active_ = true;
		return object_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxDebug::get_min_size() const {
		return object_->get_min_size();
	}
	
	sf::Vector2f BoxDebug::get_normal_size() const {
		return object_->get_normal_size();
	}
	
	IScalable& BoxDebug::get_object() {
		return *object_;
	}
	
	const IScalable& BoxDebug::get_object() const {
		return *object_;
	}
	
	void BoxDebug::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		sf::Vector2f size{this->get_area_size() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2, indent * 2})};
		size = {std::round(size.x - 2.0f), std::round(size.y - 2.0f)};
		sf::Vector2f position{this->get_area_position() + static_cast<sf::Vector2f>(sf::Vector2i{indent, indent})};
		position = {std::round(position.x + 1.0f), std::round(position.y + 1.0f)};
		
		if(drawn_ || active_) {
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			
			if(drawn_ && active_) {
				rectangle.setFillColor(sf::Color(0, 255, 0, 60));
			} else if(drawn_) {
				rectangle.setFillColor(sf::Color(255, 255, 0, 60));
			} else if(active_) {
				rectangle.setFillColor(sf::Color(255, 0, 0, 60));
			}
			
			render_target.draw(rectangle);
		}
		
		active_ = false;
		drawn_ = false;
		
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxDebug>::decode_pointer(const YAML::Node& node, BoxDebug*& box_debug) {
		box_debug = new BoxDebug{node["object"].as<BoxPtr<IScalable> >()};
		return true;

	}
	*/
}