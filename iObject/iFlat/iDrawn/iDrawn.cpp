#include "iDrawn.h"
#include <SFML/Graphics.hpp>

namespace ui {
	void IDrawn::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
	}
	
	IDrawn::IDrawn() : renderTarget(nullptr) {}
	
	bool IDrawn::updateInteractions(sf::Vector2f) {
		return true;
	}
	
	void IDrawn::update() {}
	
	void IDrawn::copy(IDrawn *iDrawn) {
		iDrawn->renderTarget = this->renderTarget;
	}
}

