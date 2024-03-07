#include "BoxDebug.hpp"
#include <cmath>

namespace ie {
	BoxDebug::Make::Make(BoxPtr<IScalable::Make>&& object) :
		object(std::move(object)) {
	}
	
	auto BoxDebug::Make::make(InitInfo init_info) -> BoxDebug* {
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
	
	auto BoxDebug::draw() -> void {
		drawn_ = true;
		object_->draw_debug(*render_target_, 0, 2, 0, 72);
	}
	
	auto BoxDebug::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	auto BoxDebug::update_interactions(sf::Vector2f mouse_position) -> bool {
		active_ = true;
		return object_->update_interactions(mouse_position);
	}
	
	auto BoxDebug::get_min_size() const -> sf::Vector2f {
		return object_->get_min_size();
	}
	
	auto BoxDebug::get_normal_size() const -> sf::Vector2f {
		return object_->get_normal_size();
	}
	
	auto BoxDebug::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxDebug::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxDebug::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		auto size{this->get_area_size() - sf::Vector2f{sf::Vector2i{indent * 2, indent * 2}}};
		size = {std::round(size.x - 2.0f), std::round(size.y - 2.0f)};
		auto position{this->get_area_position() + sf::Vector2f{sf::Vector2i{indent, indent}}};
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
}

auto ieml::Decode<char, ie::BoxDebug::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxDebug::Make> {
	return {{node.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except()}};
}
