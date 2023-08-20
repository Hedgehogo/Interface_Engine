#pragma once

#include "../baseButton.hpp"
#include "../../../../../../panel/panel/general/panel.hpp"
#include "../../../../../../panel/panel/Interaction/display/pointing/pointingDisplayPanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/display/click/clickDisplayPanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/hide/pointing/pointingHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/hide/click/clickHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/hide/dont/dontHidePanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/move/dont/dontMovePanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/move/coefficient/coefficientMovePanelInteraction.hpp"
#include "../../../../../../panel/panel/Interaction/move/Side/sideMovePanelInteraction.hpp"

namespace ui {
	class ButtonWithPanel : public BaseButton {
	public:
		struct Make : public IScalable::Make {
			BoxPtr<Panel::Make> panel;
			BoxPtr<IDisplayPanelInteraction> interaction;
			BoxPtr<IScalable::Make> background;
			
			Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable::Make>&& background);
			
			ButtonWithPanel* make(InitInfo initInfo) override;
		};
		
		ButtonWithPanel(Make&& make, InitInfo initInfo);
		
		ButtonWithPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background);
		
		ButtonWithPanel(const ButtonWithPanel& other);
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		const Panel& getPanel() const;
		
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
