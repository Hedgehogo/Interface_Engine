#include "iDrawn.h"
#include <SFML/Graphics.hpp>

namespace ui {
	void IDrawn::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->window = &window;
	}
	
	IDrawn::IDrawn() : window(nullptr) {
	}
	
	bool IDrawn::updateInteractions(sf::Vector2f) {
		return true;
	}
	
	void IDrawn::update() {
	}
	
	void IDrawn::copy(IDrawn *iDrawn) {
		iDrawn->window = this->window;
	}
}

