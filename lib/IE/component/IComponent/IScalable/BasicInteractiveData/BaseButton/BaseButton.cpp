#include "BaseButton.hpp"

namespace ie {
	BaseButton::BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo init_info) :
		background(background->make(init_info)) {
		init_info.update_manager.add(*this);
	}
	
	BaseButton::BaseButton(BoxPtr<IScalable>&& background) :
		background(std::move(background)) {
	}
	
	void BaseButton::init(InitInfo init_info) {
		init_info.update_manager.add(*this);
		background->init(init_info);
	}
	
	IScalable& BaseButton::get_object() {
		return *background;
	}
	
	const IScalable& BaseButton::get_object() const {
		return *background;
	}
	
	bool BaseButton::update_interactions(sf::Vector2f mouse_position) {
		return background->update_interactions(mouse_position);
	}
	
	LayoutData& BaseButton::layout_get_data() {
		return layout;
	}
	
	const LayoutData& BaseButton::layout_get_data() const {
		return layout;
	}
	
	void BaseButton::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}