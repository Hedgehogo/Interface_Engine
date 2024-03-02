#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "Sizing2InitInfo/Sizing2InitInfo.hpp"

namespace ie {
	class ISizing2 {
	public:
		struct Make {
			virtual auto make(Sizing2InitInfo init_info) -> ISizing2* = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~ISizing2() = default;
		
		virtual auto find_size(sf::Vector2f parent_size) -> sf::Vector2f = 0;
		
		virtual auto get_parent_size(sf::Vector2f object_size) -> sf::Vector2f = 0;
		
		auto operator()(sf::Vector2f parent_size) -> sf::Vector2f;
	};
}
