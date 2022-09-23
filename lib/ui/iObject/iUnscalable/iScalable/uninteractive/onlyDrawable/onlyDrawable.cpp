#include "onlyDrawable.hpp"

namespace ui {
    void OnlyDrawable::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
        drawManager.add(*this);
        this->renderTarget = &renderTarget;
    }

    OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {}

    bool OnlyDrawable::updateInteractions(sf::Vector2f mousePosition) {
        return IUninteractive::updateInteractions(mousePosition);
    }

    void OnlyDrawable::copy(OnlyDrawable *onlyDrawable) {
        onlyDrawable->renderTarget = this->renderTarget;
    }
}