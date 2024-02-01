#include "BaseButton.hpp"

namespace ie {
	BaseButton::BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo init_info) :
		background_(background->make(init_info)) {
		init_info.update_manager.add(*this);
	}
	
	IScalable& BaseButton::get_object() {
		return *background_;
	}
	
	const IScalable& BaseButton::get_object() const {
		return *background_;
	}
	
	bool BaseButton::update_interactions(sf::Vector2f mouse_position) {
		return background_->update_interactions(mouse_position);
	}
	
	LayoutData& BaseButton::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& BaseButton::layout_get_data() const {
		return layout_;
	}
	
	void BaseButton::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}