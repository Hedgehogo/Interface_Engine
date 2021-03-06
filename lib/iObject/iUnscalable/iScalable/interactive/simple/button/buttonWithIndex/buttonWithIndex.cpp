#include "buttonWithIndex.h"

namespace ui {
	void ButtonWithIndex::init(sf::RenderTarget &renderTarget, PanelManager &panelManager) {
		Button::init(renderTarget, panelManager);
		interaction = interactionStack->at(interactionIndex);
	}
	
	ButtonWithIndex::ButtonWithIndex(ui::OnlyDrawable *background, uint16_t interaction) :
		Button(background, nullptr), interactionIndex(interaction) {}
	
	ButtonWithIndex *ButtonWithIndex::copy() {
		ButtonWithIndex* buttonWithIndex{new ButtonWithIndex{dynamic_cast<OnlyDrawable*>(background->copy()), interactionIndex}};
		Button::copy(buttonWithIndex);
		buttonWithIndex->interaction = this->interaction;
		return buttonWithIndex;
	}
}
