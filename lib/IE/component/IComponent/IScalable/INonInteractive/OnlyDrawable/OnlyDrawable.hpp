#pragma once

#include "../INonInteractive.hpp"

namespace ie {
	class OnlyDrawable : public virtual INonInteractive, public virtual IDrawable {
	public:
		OnlyDrawable(InitInfo init_info);
		
		OnlyDrawable();
		
		sf::RenderTarget& get_render_target();
		
	protected:
		sf::RenderTarget* render_target_;
	};
}