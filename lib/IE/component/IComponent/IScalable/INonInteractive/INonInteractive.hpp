#pragma once

#include "../IScalable.hpp"

namespace ie {
	class INonInteractive : public virtual IScalable {
	public:
		struct Make : public virtual IScalable::Make {
			virtual auto make(InitInfo init_info) -> INonInteractive* = 0;
		};
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
	};
}
