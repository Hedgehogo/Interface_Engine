#include "buttonWithIndex.h"

namespace ui {
	void ButtonWithIndex::init(sf::RenderWindow &window, Panel *parent, PanelStack &overlayStack) {
		Button::init(window, parent, overlayStack);
		interaction = interactionStack->at(interactionIndex);
	}
	
	ButtonWithIndex::ButtonWithIndex(ui::IDrawn *background, uint16_t interaction) :
		Button(background, nullptr), interactionIndex(interaction) {}
}
