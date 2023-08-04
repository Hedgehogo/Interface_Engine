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
	public:
		ButtonWithPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background);
		
		ButtonWithPanel(const ButtonWithPanel& other);
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		ButtonWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<Panel> panel;
	};
	
	template<>
	struct DecodePointer<ButtonWithPanel> {
		static bool decodePointer(const YAML::Node& node, ButtonWithPanel*& buttonWithPanel);
	};
}
