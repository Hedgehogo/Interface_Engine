#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"
#include "../Box.hpp"

namespace ie {
	class BoxWithView : public Box, public virtual IDrawable {
	public:
		BoxWithView(sf::Vector2f min_size, InitInfo init_info);
		
		BoxWithView(sf::Vector2f min_size);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
	protected:
		DrawManager draw_manager_;
		sf::RenderTarget* render_target_;
		sf::View view_;
	};
}