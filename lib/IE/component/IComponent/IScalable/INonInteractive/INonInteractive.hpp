#pragma once

#include "../IScalable.hpp"

namespace ie {
	class INonInteractive : public virtual IScalable {
	public:
		struct Make : public virtual IScalable::Make {
			virtual INonInteractive* make(InitInfo init_info) = 0;
		};
		
		bool update_interactions(sf::Vector2f mouse_position) override;
	};
}
