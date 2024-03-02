#pragma once

#include "../INonInteractive.hpp"

namespace ie {
	class OnlyDrawable : public virtual INonInteractive, public virtual IDrawable {
	public:
		OnlyDrawable(InitInfo init_info);
		
		OnlyDrawable();
		
		auto get_render_target() -> sf::RenderTarget&;
		
	protected:
		sf::RenderTarget* render_target_;
	};
}