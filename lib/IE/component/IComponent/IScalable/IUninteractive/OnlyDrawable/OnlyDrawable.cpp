#include "OnlyDrawable.hpp"

namespace ie {
	OnlyDrawable::OnlyDrawable() : render_target(nullptr) {
	}
	
	void OnlyDrawable::init(InitInfo init_info) {
		init_info.draw_manager.add(*this);
		this->render_target = &init_info.render_target;
	}
	
	OnlyDrawable::OnlyDrawable(InitInfo init_info) : render_target(&init_info.render_target) {
		init_info.draw_manager.add(*this);
	}
	
	sf::RenderTarget& OnlyDrawable::get_render_target() {
		return *render_target;
	}
}