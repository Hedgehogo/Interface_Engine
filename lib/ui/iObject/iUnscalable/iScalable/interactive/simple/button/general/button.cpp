#include "button.hpp"

namespace ui {
    Button::Button(ui::OnlyDrawable *background, uint16_t interaction) :
        BaseButton(background, nullptr), interactionIndex(interaction) {}

    void Button::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) {
		BaseButton::init(renderTarget, drawManager, updateManager, panelManager);
		interaction = interactionStack->at(interactionIndex);
	}

	Button *Button::copy() {
		Button* buttonWithIndex{new Button{dynamic_cast<OnlyDrawable*>(background->copy()), interactionIndex}};
		BaseButton::copy(buttonWithIndex);
		buttonWithIndex->interaction = this->interaction;
		return buttonWithIndex;
	}

    Button *Button::createFromYaml(const YAML::Node &node) {

        ui::OnlyDrawable *background;
        uint16_t interaction;

        node["background"] >> background;
        node["interaction"] >> interaction;

        return new Button{background, interaction};
    }
}
