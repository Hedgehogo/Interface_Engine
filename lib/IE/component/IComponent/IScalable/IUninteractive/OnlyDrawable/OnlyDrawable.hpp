#pragma once

#include "../IUninteractive.hpp"

namespace ie {
	class OnlyDrawable : public virtual IUninteractive, public virtual IDrawable {
	public:
		OnlyDrawable(InitInfo init_info);
		
		OnlyDrawable();
		
		sf::RenderTarget& get_render_target();
		
		void init(InitInfo init_info) override;
	
	protected:
		sf::RenderTarget* render_target;
	};
}