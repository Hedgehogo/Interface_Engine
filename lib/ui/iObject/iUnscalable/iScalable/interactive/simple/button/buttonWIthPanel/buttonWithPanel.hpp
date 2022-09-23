#pragma once
#include "../baseButton.hpp"
#include "../../../../../../panel/panel/general/panel.hpp"
#include "../../../../../../panel/panel/interaction/display/pointing/pointingDisplayPanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/display/click/clickDisplayPanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/hide/pointing/pointingHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/hide/click/clickHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/hide/dont/dontHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/move/dont/dontMovePanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/move/coefficient/coefficientMovePanelInteraction.hpp"
#include "../../../../../../panel/panel/interaction/move/side/sideMovePanelInteraction.hpp"

namespace ui {
	class ButtonWithPanel : public BaseButton {
	protected:
		Panel *panel;
		
	public:
		ButtonWithPanel(Panel *panel, DisplayPanelInteraction* interaction, IScalable *background);
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) override;
		
		~ButtonWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		ButtonWithPanel* copy() override;
		
		static ButtonWithPanel* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
