#include "BaseButton.hpp"

namespace ie {
	BaseButton::BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo init_info) :
		background_(background->make(init_info)) {
		init_info.update_manager.add(*this);
	}
	
	auto BaseButton::get_object() -> IScalable& {
		return *background_;
	}
	
	auto BaseButton::get_object() const -> IScalable const& {
		return *background_;
	}
	
	auto BaseButton::handle_event(Event event) -> bool {
		return background_->handle_event(event);
	}
	
	auto BaseButton::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto BaseButton::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
	
	auto BaseButton::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}