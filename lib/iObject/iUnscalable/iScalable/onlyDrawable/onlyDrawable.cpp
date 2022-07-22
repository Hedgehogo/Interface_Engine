#include "onlyDrawable.h"
#include <SFML/Graphics.hpp>

namespace ui {
	void OnlyDrawable::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
	}
	
	OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {}
	
	bool OnlyDrawable::updateInteractions(sf::Vector2f) {
		return true;
	}
	
	void OnlyDrawable::update() {}
	
	void OnlyDrawable::copy(OnlyDrawable *onlyDrawable) {
		onlyDrawable->renderTarget = this->renderTarget;
	}
}

