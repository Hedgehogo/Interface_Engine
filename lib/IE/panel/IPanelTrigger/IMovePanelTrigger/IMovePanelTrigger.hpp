#pragma once

#include "../IPanelTrigger.hpp"

namespace ie {
	class IMovePanelTrigger : public virtual IPanelTrigger {
	public:
		struct Make : public virtual IPanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> IMovePanelTrigger* override = 0;
		};
		
		virtual auto move(sf::Vector2i offset) -> void = 0;
	};
}
