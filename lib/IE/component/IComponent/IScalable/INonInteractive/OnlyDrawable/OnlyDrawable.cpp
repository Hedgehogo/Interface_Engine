#include "OnlyDrawable.hpp"

namespace ie {
	OnlyDrawable::OnlyDrawable() : render_target_(nullptr) {
	}
	
	OnlyDrawable::OnlyDrawable(InitInfo init_info) : render_target_(&init_info.render_target) {
		init_info.draw_manager.add(*this);
	}
	
	auto OnlyDrawable::get_render_target() -> sf::RenderTarget& {
		return *render_target_;
	}
}