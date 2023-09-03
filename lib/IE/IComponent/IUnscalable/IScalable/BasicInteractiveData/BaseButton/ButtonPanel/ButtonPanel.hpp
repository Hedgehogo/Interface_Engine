#pragma once

#include "../BaseButton.hpp"
#include "../../../../../Panel/BasePanel/Panel/Panel.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IDisplayPanelInteraction/PointingDisplayPanelInteraction/PointingDisplayPanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IDisplayPanelInteraction/ClickDisplayPanelInteraction/ClickDisplayPanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IHidePanelInteraction/PointingHidePanelInteraction/PointingHidePanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IHidePanelInteraction/ClickHidePanelInteraction/ClickHidePanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IHidePanelInteraction/DontHidePanelInteraction/DontHidePanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IMovePanelInteraction/DontMovePanelInteraction/DontMovePanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IMovePanelInteraction/CoefficientMovePanelInteraction/CoefficientMovePanelInteraction.hpp"
#include "IE/IComponent/Panel/IPanelInteraction/IMovePanelInteraction/SideMovePanelInteraction/SideMovePanelInteraction.hpp"

namespace ie {
	class ButtonPanel : public BaseButton {
	public:
		struct Make : public virtual ILayoutObject::Make, public virtual IScalable::Make {
			BoxPtr<Panel::Make> panel;
			BoxPtr<IDisplayPanelInteraction::Make> interaction;
			BoxPtr<IScalable::Make> background;
			
			Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction::Make>&& interaction, BoxPtr<IScalable::Make>&& background);
			
			ButtonPanel* make(InitInfo initInfo) override;
		};
		
		ButtonPanel(Make&& make, InitInfo initInfo);
		
		ButtonPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background);
		
		ButtonPanel(const ButtonPanel& other);
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		const Panel& getPanel() const;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		ButtonPanel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<Panel> panel;
		BasicInteractiveData<Panel&> interactive;
	};
	
	template<>
	struct DecodePointer<ButtonPanel> {
		static bool decodePointer(const YAML::Node& node, ButtonPanel*& buttonWithPanel);
	};
}
