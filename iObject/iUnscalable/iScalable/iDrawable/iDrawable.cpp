#include "iDrawable.h"
#include <SFML/Graphics.hpp>

namespace ui {
	void IDrawable::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
	}
	
	IDrawable::IDrawable() : renderTarget(nullptr) {}
	
	bool IDrawable::updateInteractions(sf::Vector2f) {
		return true;
	}
	
	void IDrawable::update() {}
	
	void IDrawable::copy(IDrawable *iDrawn) {
		iDrawn->renderTarget = this->renderTarget;
	}
}

