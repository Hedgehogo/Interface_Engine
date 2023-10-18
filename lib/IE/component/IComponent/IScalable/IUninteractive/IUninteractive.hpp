#pragma once

#include "../IScalable.hpp"

namespace ie {
	class IUninteractive : public virtual IScalable {
	public:
		struct Make : public virtual IScalable::Make {
			virtual IUninteractive* make(InitInfo init_info) = 0;
		};
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		IUninteractive* copy() override = 0;
	};
}
