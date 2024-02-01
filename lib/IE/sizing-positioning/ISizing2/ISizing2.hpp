#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "Sizing2InitInfo/Sizing2InitInfo.hpp"

namespace ie {
	class ISizing2 {
	public:
		struct Make {
			virtual ISizing2* make(Sizing2InitInfo init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~ISizing2() = default;
		
		virtual sf::Vector2f find_size(sf::Vector2f parent_size) = 0;
		
		virtual sf::Vector2f get_parent_size(sf::Vector2f object_size) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parent_size);
	};
}
