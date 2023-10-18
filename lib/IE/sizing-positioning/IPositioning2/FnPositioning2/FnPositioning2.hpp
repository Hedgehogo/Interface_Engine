#pragma once

#include "../IPositioning2.hpp"

namespace ie {
	class FnPositioning2 : public virtual IPositioning2 {
	public:
		using FindPositionFn = std::function<sf::Vector2f(
			sf::Vector2f parent_position,
			sf::Vector2f object_size,
			sf::Vector2f parent_size,
			sf::Vector2f target_size
		)>;
		
		struct Make : public virtual IPositioning2::Make {
			FindPositionFn find_position_fn;
			
			Make(FindPositionFn find_position_fn);
			
			FnPositioning2* make(Positioning2InitInfo init_info) override;
		};
		
		FnPositioning2(Make&& make, Positioning2InitInfo init_info);
		
		FnPositioning2(FindPositionFn find_position_fn);
		
		void init(sf::RenderTarget& render_target) override;
		
		sf::Vector2f find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) override;
		
		FnPositioning2* copy() override;
	
	protected:
		FindPositionFn find_position_fn;
		sf::RenderTarget* render_target;
	};
}
