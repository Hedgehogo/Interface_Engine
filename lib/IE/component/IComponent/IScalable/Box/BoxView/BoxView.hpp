#pragma once

#include "../Box.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"

namespace ie {
	class BoxWithView : public Box, public virtual IDrawable {
	public:
		BoxWithView(sf::Vector2f min_size, InitInfo init_info);
		
		BoxWithView(sf::Vector2f min_size);
		
		BoxWithView(const BoxWithView& other);
		
		void init(InitInfo init_info) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		BoxWithView* copy() override = 0;
	
	protected:
		DrawManager draw_manager_;
		sf::RenderTarget* render_target_;
		sf::View view_;
	};
}