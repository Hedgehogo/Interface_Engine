#include "button.hpp"

namespace ui {
    Button::Button(IUninteractive *background, int interaction) :
        BaseButton(background, nullptr), interactionIndex(interaction) {}

	Button::Button(IUninteractive *background, IInteraction *interaction) : BaseButton(background, interaction), interactionIndex(-1) {}

    void Button::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
	    if (interactionIndex >= 0)
		    interaction = interactionStack->at(interactionIndex);
		BaseButton::init(renderTarget, drawManager, updateManager, panelManager);
	}

	Button *Button::copy() {
		Button* buttonWithIndex{new Button{dynamic_cast<IUninteractive*>(background->copy()), interactionIndex}};
		BaseButton::copy(buttonWithIndex);
		buttonWithIndex->interaction = this->interaction;
		return buttonWithIndex;
	}

    bool convertPointer(const YAML::Node &node, Button *&button) {
        IUninteractive *background;

        node["background"] >> background;

		if (node["interaction"]) {
			IInteraction *interaction;
			node["interaction"] >> interaction;
			{ button = new Button{background, interaction}; return true; }
		}

		int index;
		node["index"] >> index;
	
		{ button = new Button{background, index}; return true; }
    }
}
