#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"
#include "../Box.hpp"

namespace ie {
	class BoxView : public Box, public virtual IDrawable {
	public:
		BoxView(sf::Vector2f min_size, InitInfo init_info);
		
		BoxView(sf::Vector2f min_size);
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
	protected:
		DrawManager draw_manager_;
		sf::RenderTarget* render_target_;
		sf::View view_;
	};
}