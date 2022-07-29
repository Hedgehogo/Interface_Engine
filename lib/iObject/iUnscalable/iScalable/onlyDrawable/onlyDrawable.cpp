#include "onlyDrawable.h"
#include <SFML/Graphics.hpp>

namespace ui {
	void OnlyDrawable::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		drawManager.add(*this);
		this->renderTarget = &renderTarget;
	}
	
	OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {}
	
	bool OnlyDrawable::updateInteractions(sf::Vector2f) {
		return true;
	}
	
	void OnlyDrawable::copy(OnlyDrawable *onlyDrawable) {
		onlyDrawable->renderTarget = this->renderTarget;
	}
}

